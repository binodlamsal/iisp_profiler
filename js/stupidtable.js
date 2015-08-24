// Stupid jQuery table plugin.

(function($) {
  $.fn.stupidtable = function(sortFns) {
    return this.each(function() {
      var $table = $(this);
      sortFns = sortFns || {};
      sortFns = $.extend({}, $.fn.stupidtable.default_sort_fns, sortFns);
      $table.data('sortFns', sortFns);

      $table.on("click.stupidtable", "thead th", function() {
          $(this).stupidsort();
      });
    });
  };


  // Expects $("#mytable").stupidtable() to have already been called.
  // Call on a table header.
  $.fn.stupidsort = function(force_direction){
    var $this_th = $(this);
    var th_index = 0; // we'll increment this soon
    var dir = $.fn.stupidtable.dir;
    var $table = $this_th.closest("table");
    var datatype = $this_th.data("sort") || null;

    // No datatype? Nothing to do.
    if (datatype === null) {
      return;
    }

    // Account for colspans
    $this_th.parents("tr").find("th").slice(0, $(this).index()).each(function() {
      var cols = $(this).attr("colspan") || 1;
      th_index += parseInt(cols,10);
    });

    var sort_dir;
    if(arguments.length == 1){
        sort_dir = force_direction;
    }
    else{
        sort_dir = force_direction || $this_th.data("sort-default") || dir.ASC;
        if ($this_th.data("sort-dir"))
           sort_dir = $this_th.data("sort-dir") === dir.ASC ? dir.DESC : dir.ASC;
    }


    $table.trigger("beforetablesort", {column: th_index, direction: sort_dir});

    // More reliable method of forcing a redraw
    $table.css("display");

    // Run sorting asynchronously on a timout to force browser redraw after
    // `beforetablesort` callback. Also avoids locking up the browser too much.
    setTimeout(function() {
      // Gather the elements for this column
      var column = [];
      var sortFns = $table.data('sortFns');
      var sortMethod = sortFns[datatype];
      var trs = $table.children("tbody").children("tr");

      // Extract the data for the column that needs to be sorted and pair it up
      // with the TR itself into a tuple. This way sorting the values will
      // incidentally sort the trs.
      trs.each(function(index,tr) {
        var $e = $(tr).children().eq(th_index);
        var sort_val = $e.data("sort-value");

        // Store and read from the .data cache for display text only sorts
        // instead of looking through the DOM every time
        if(typeof(sort_val) === "undefined"){
          var txt = $e.text();
          $e.data('sort-value', txt);
          sort_val = txt;
        }
        column.push([sort_val, tr]);
      });

      // Sort by the data-order-by value
      column.sort(function(a, b) { return sortMethod(a[0], b[0]); });
      if (sort_dir != dir.ASC)
        column.reverse();

      // Replace the content of tbody with the sorted rows. Strangely
      // enough, .append accomplishes this for us.
      trs = $.map(column, function(kv) { return kv[1]; });
      $table.children("tbody").append(trs);

      // Reset siblings
      $table.find("th").data("sort-dir", null).removeClass("sorting-desc sorting-asc");
      $this_th.data("sort-dir", sort_dir).addClass("sorting-"+sort_dir);

      $table.trigger("aftertablesort", {column: th_index, direction: sort_dir});
      $table.css("display");
    }, 10);

    return $this_th;
  };

  // Call on a sortable td to update its value in the sort. This should be the
  // only mechanism used to update a cell's sort value. If your display value is
  // different from your sort value, use jQuery's .text() or .html() to update
  // the td contents, Assumes stupidtable has already been called for the table.
  $.fn.updateSortVal = function(new_sort_val){
  var $this_td = $(this);
    if($this_td.is('[data-sort-value]')){
      // For visual consistency with the .data cache
      $this_td.attr('data-sort-value', new_sort_val);
    }
    $this_td.data("sort-value", new_sort_val);
    return $this_td;
  };

  // ------------------------------------------------------------------
  // Default settings
  // ------------------------------------------------------------------
  $.fn.stupidtable.dir = {ASC: "asc", DESC: "desc"};
  $.fn.stupidtable.default_sort_fns = {
    "int": function(a, b) {
      return parseInt(a, 10) - parseInt(b, 10);
    },
    "float": function(a, b) {
      return parseFloat(a) - parseFloat(b);
    },
    "string": function(a, b) {
      return a.localeCompare(b);
    },
    "string-ins": function(a, b) {
      a = a.toLocaleLowerCase();
      b = b.toLocaleLowerCase();
      return a.localeCompare(b);
    }
  };
})(jQuery);


 jQuery(function($){
      // Helper function to convert a string of the form "Mar 15, 1987" into
      // a Date object.
      var date_from_string = function(str){
        var months = ["jan","feb","mar","apr","may","jun","jul",
                      "aug","sep","oct","nov","dec"];
        var pattern = "^([a-zA-Z]{3})\\s*(\\d{2}),\\s*(\\d{4})$";
        var re = new RegExp(pattern);
        var DateParts = re.exec(str).slice(1);

        var Year = DateParts[2];
        var Month = $.inArray(DateParts[0].toLowerCase(), months);
        var Day = DateParts[1];
        return new Date(Year, Month, Day);
      }

      var moveBlanks = function(a, b) {
        if ( a < b ){
          if (a == "")
            return 1;
          else
            return -1;
        }
        if ( a > b ){
          if (b == "")
            return -1;
          else
            return 1;
        }
        return 0;
      };
      var moveBlanksDesc = function(a, b) {
        // Blanks are by definition the smallest value, so we don't have to
        // worry about them here
        if ( a < b )
          return 1;
        if ( a > b )
          return -1;
        return 0;
      };

      var table = $("table").stupidtable({
        "date":function(a,b){
          // Get these into date objects for comparison.

          aDate = date_from_string(a);
          bDate = date_from_string(b);

          return aDate - bDate;
        },
        "moveBlanks": moveBlanks,
        "moveBlanksDesc": moveBlanksDesc,
      });

      table.on("beforetablesort", function (event, data) {
        // data.column - the index of the column sorted after a click
        // data.direction - the sorting direction (either asc or desc)
        $("#msg").text("Sorting index " + data.column)
      });

      table.on("aftertablesort", function (event, data) {
        var th = $(this).find("th");
        th.find(".arrow").remove();
        var dir = $.fn.stupidtable.dir;

        var arrow = data.direction === dir.ASC ? "&uarr;" : "&darr;";
        th.eq(data.column).append('<span class="arrow">' + arrow +'</span>');
      });

      $("tr").slice(1).click(function(){
        $(".awesome").removeClass("awesome");
        $(this).addClass("awesome");
      });

    });