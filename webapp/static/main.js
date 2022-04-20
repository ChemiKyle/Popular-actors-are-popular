$(document).ready(function() {
  // initial page load
  // make user wait until data structures are populated
  if (!structures_ready) {
    $.ajax({
      url: "/buildStructures",
      cache: false,
      beforeSend: function(){
        $('#wait').show();
        $("form").hide();
      },
      complete: function(){
        $('#wait').hide();
        $("form").show();
      },
      success: function(response){
        structures_ready = response['structures_ready'];
        build_time = response['build_time'] / (1000**2);
        $("#build_time").html(`Building structures took ${build_time.toFixed(2)} seconds`);
      }
    });
  }

  // fetch random data
  $("#simulate_random").on('click', function(e) {
    $.ajax(
      {
        url: "/getRandom",
        type: "GET",
      }
    )
     .done(function(data) {

       hash_data = data['hash_data'];
       splay_data = data['splay_data'];

       Plotly.newPlot(
         'plotly_chart',
         [hash_data, splay_data],
         layout
       );

       // Update plot
       Plotly.update(
         'plotly_chart',
         [hash_data, splay_data],
         layout
       );
     });

  });

  // fetch simulated data
  $("#simulate_popular").on('click', function(e) {
    $.ajax(
      {
        url: "/simulate",
        type: "GET",
      }
    )
     .done(function(data) {

       let index = splay_data["x"].length ? (Math.max(...splay_data["x"])) : 0;

       for (let i = 1; i < data["name"].length; i++) {
         hash_data["x"].push(index + i);
         splay_data["x"].push(index + i);
       }

       hash_data["text"] = hash_data["text"].concat(data["name"]);
       hash_data["y"]= hash_data["y"].concat(data["hash_time"]);

       splay_data["text"] = splay_data["text"].concat(data["name"]);
       splay_data["y"] = splay_data["y"].concat(data["splay_time"]);

       // Update plot
       Plotly.update(
         'plotly_chart',
         [hash_data, splay_data],
         layout
       );
     });

  });

  // get runtimes from cpp after clicking submit
  // use them to update the plot
  $("form").on('submit', function(e) {
    e.preventDefault();

    $.ajax(
      {
        url: "/ajax",
        type: "GET",
        data: {"search": $("#search").val()}
      }
    )
     .done(function(data) {

       // return 0 if array is empty
       let index = splay_data["x"].length ? (Math.max(...splay_data["x"])) : 0;

       // update plot values
       hash_data["text"].push(data["name"]);
       hash_data["y"].push(data["hash_time"]);

       splay_data["text"].push(data["name"]);
       splay_data["y"].push(data["splay_time"]);

       hash_data["x"].push(index + 1);
       splay_data["x"].push(index + 1);

       // Update plot
       Plotly.update(
         'plotly_chart',
         [hash_data, splay_data],
         layout
       );
     });

  });

});

// plotly chart layout
var layout = {
  xaxis: {
    title: "Query number",
    tick0: 0
  },
  yaxis: {
    title: "Time to locate (ns)",
    tick0: 0
  },
  hovermode: "x",
  title: "Search performance"
};
