library(tidyverse)
library(DBI)
library(janitor)
library(furrr)

plan(multicore)

###############################################################################
#                       Read in tsv files as dataframes                       #
###############################################################################


# data sourced from: https://datasets.imdbws.com/
# actors.tsv is from: name.basics.tsv.gz
# the file after un-gzipping is data.tsv, which was renamed
system.time({
  a_df <- read_tsv("actors.tsv") %>%
    # convert camelCase column names to snake_case
    clean_names()
})
 ##   user  system elapsed
 ## 44.231   1.949  41.370

# data.tsv is from: title.basics.tsv.gz
system.time({
  t_df <- read_tsv("data.tsv") %>%
    clean_names()
})


# Dump dataframes into a SQLite database in hopes of faster performance #######
# NOTE: this did not actually end up improving performance, but I've left it here anyway
# I did the data cleaning on a device with 32GB, 3733 MHz clock speed RAM
if (FALSE) {
  # Creates file if one does not exist
  con <- dbConnect(
    RSQLite::SQLite(),
    ## dbname = "imdb.db"
    dbname = "~/projects/personal/2022_spring_dsa_p3/data/imdb.db"
  )

  dbWriteTable(
    conn = con,
    name = "actors",
    value = a_df
  )

  # create local dataframe from database,
  # hope was that this would be significantly faster than read_tsv, but time savings were minimal
  system.time({
    a_df <- tbl(con, "actors") %>%
      collect()
  })
  ## user  system elapsed
  ## 37.911   0.785  39.382

  dbWriteTable(
    conn = con,
    name = "titles",
    value = t_df
  )
}

###############################################################################
#                               Data janitoring                               #
###############################################################################
# Combine our two datasets into one

# adapted from: https://stackoverflow.com/a/33288868/7418735

# create a row for each title an actor was "known for"
system.time({
  long_adf <- a_df %>%
    mutate(title_ids = strsplit(known_for_titles, ",")) %>%
    select(-known_for_titles) %>%
    unnest(title_ids) %>%
    group_by(nconst) %>%
    mutate(row = row_number()) %>%
    ungroup()
})
## user  system elapsed
## 297.692   3.125 303.198
# result is ~ 20 million rows
# a_df is ~ 10 million rows

system.time({
  simple_tdf <- t_df %>%
    mutate(info = paste0(primary_title, " - ", start_year)) %>%
    select(tconst, info)
})
##   user  system elapsed
##   3.766   0.017   3.812

system.time({
  long_joined_df <- long_adf %>%
    left_join(simple_tdf, by = c("title_ids" = "tconst"))
})
##   user  system elapsed
##   9.763   0.388  10.203

system.time({
  simple_joined_df <- long_joined_df %>%
    # collapse rows for actors, each title becomes a column
    pivot_wider(
      id_cols = c(everything(), -title_ids),
      names_from = row,
      names_glue = "title_{row}",
      values_from = info
    ) %>%
    # collapse titles into a single column
    unite(
      col = "titles",
      starts_with("title_"),
      # use pipe for delim to ease parsing later
      sep = "|"
    )
})
## user  system elapsed
## 18.449   1.158  19.998

## simple_joined_df %>%
##   write_csv("actors_with_titles.csv")
# 1.1 GB file

minimal_joined_df <- simple_joined_df %>%
  # delete commas from the data set
  # don't have to program edge cases if you just remove them
  select(nconst, primary_name, titles) %>%
  mutate(
    primary_name = str_replace_all(primary_name, ",", ""),
    titles = str_replace_all(titles, ",", "")
  )

minimal_joined_df %>%
  write_csv("actors_with_titles.csv")
# 843 MB file

###############################################################################
#                                 Scratch area                                #
###############################################################################

# get a breakdown of the types of media represented in the data
t_df %>%
  count(title_type) %>%
  arrange(desc(n))
##    title_type         n
##    <chr>          <int>
##  1 tvEpisode    6630770
##  2 short         864355
##  3 movie         606969
##  4 video         259174
##  5 tvSeries      223371
##  6 tvMovie       135691
##  7 tvMiniSeries   42949
##  8 tvSpecial      36529
##  9 videoGame      30866
## 10 tvShort        10514
## 11 tvPilot            2

# confirm all IDs start with "nm"
a_df %>%
  count(substr(nconst, 1, 2))


# get the row count to decide on an optimal default initial size for our Hash Table
df <- read_csv("data/actors_with_titles.csv")

df %>%
  nrow()
# 11456063
