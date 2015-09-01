jQuery(document).ready(function($) {
	var root = document.location.hostname;
	 var pathArray = window.location.pathname.split( '/' );
	 var secondLevelLocation = pathArray[1];
	 var base_url = 'http://'+root;
	$('.toggle-span').click(function(){
		$( ".inner-accordion" ).slideToggle( "slow", function() {});
	});

	var profile_info_id = $("#profile_info_id").val(); 

	$.ajax({
                url: base_url + '/iisp_skills/ajax_skills_profile_data/'+profile_info_id,
                data: {"test":"test"},
                dataType: 'json',
                method:'POST',
                  success:function (data)
                  {
                  		$.each(data, function(key,val) {
                  					var score = val.score;
                  					var skillLevel = val.iisp_skills_id;
                  				   $('#setLevelDiv'+skillLevel + ' .level-set').text('Level ' + score); 
								   $('#setlevel-btn-value'+skillLevel).text('Set Level ' + score); 
								   $('#setlevel-btn-value'+skillLevel).attr("data-checkboxid",score);
								   $('#checkbox-'+score+'-skill-'+skillLevel).css("background-color", "green");
						  });
                  },
              });

	$('#viewing_profile_id').change(function(){
			window.location.replace(base_url + "/?q=iisp_profiler/profiles/skill/" + $('#viewing_profile_id').val());
	});

});
