jQuery(document).ready(function($) {
	var root = document.location.hostname;
	 var pathArray = window.location.pathname.split( '/' );
	 var secondLevelLocation = pathArray[1];
	 var base_url = 'http://'+root;
	 $('.share_div').hide();
	$('.toggle-span').click(function(){
		$( ".inner-accordion" ).slideToggle( "slow", function() {});
	});

	$('body').on('click', '.share_info', function(){
		var radio_share_val_yes =$('#share_info_yes_id').val();
		var radio_share_val_no =$('#share_info_no_id').val();
		if($("#share_info_yes_id").is(":checked")){
			$('.share_div').show();
		}else{
			$('.share_div').hide();
		}
	});


	var profile_info_id = $("#profile_info_id").val();
	debugger;

	$.ajax({
                url: base_url + '/'+ secondLevelLocation +'/iisp_skills/ajax_skills_category_total',
                data: {"iisp_profiles_id":profile_info_id},
                dataType: 'json',
                method:'POST',
                  success:function (data)
                  {
                  		$.each(data, function(key,val) {
                  					var score = val.tot_score;
                  					var cat_id = val.skill_cat_id;
                  				   $('#skill_catid_total_'+cat_id).text('Total - ' + score); 
						  });
                  },
                  error: function() {
				    //error loading content
				  },
				  complete: function() {
				  	$('.score-not-set').css('background-color','green');
				  }
    });

	$.ajax({
                url: base_url + '/'+ secondLevelLocation +'/iisp_skills/ajax_skills_profile_data/'+profile_info_id,
                data: {"test":"test"},
                dataType: 'json',
                method:'POST',
                  success:function (data)
                  {
                  		$.each(data, function(key,val) {
                  					var score = val.score;
                  					var skillLevel = val.iisp_skills_id;
                  				   $('#setLevelDiv'+skillLevel + ' .level-set').text('Level ' + score); 
								   $('#setlevel-btn-value'+skillLevel).text('Level ' + score); 
								   $('#setlevel-btn-value'+skillLevel).attr("data-checkboxid",score);
								   $('#checkbox-'+score+'-skill-'+skillLevel).css("background-color", "green");
								   $('#checkbox-'+score+'-skill-'+skillLevel).css("border", "1px dotted #000");
								   $('#checkbox-reset-skill-'+skillLevel).removeClass("score-not-set");
								   $('#checkbox-reset-skill-'+skillLevel).addClass("score-already-set");
						  });
                  },
                  error: function() {
				    //error loading content
				  },
				  complete: function() {
				  	$('.score-not-set').css('background-color','green');
				  }
              });

	$('#viewing_profile_id').change(function(){
		//alert(base_url); 
			window.location.replace(base_url + "/?q=iisp_profiler/profiles/skill/" + $('#viewing_profile_id').val());
	});

	//Comparing javascript addition from this belowSS
	
	$('body').on('click','.user-add-class',function(){
		var profile_pos_id = $(this).attr("data-profile-pos-id");
		$('#profile-pos-id-'+profile_pos_id).attr('data-toggle','modal');
        $('#profile-pos-id-'+profile_pos_id).attr('data-target','#myModal');
		$('#myModal').attr("data-modal-pos-id",profile_pos_id);
	});

	$('body').on('click','.remove-profile-class',function(){
		var profile_pos_id = $(this).attr("data-profile-pos-id");
        $('.checkbox-pos-'+profile_pos_id).css("background-color", "#ccc"); 
        $('.checkbox-pos-'+profile_pos_id).text('-'); 
        $('#profile-pos-id-'+profile_pos_id).text('Add');
        $('#profile-pos-id-'+profile_pos_id).removeClass('btn-danger');
        $('#profile-pos-id-'+profile_pos_id).addClass('btn-default');
        $('#profile-pos-id-'+profile_pos_id).addClass('user-add-class');
        $('#profile-pos-id-'+profile_pos_id).removeClass('remove-profile-class');
	});

	//statically add all value while page loading for first position
	setTimeout(function() {
		$('#myModal').attr("data-modal-pos-id",1);
		$('#add_profile_id').val(pathArray[4]);
        $(".btn-save-ap").trigger('click');
    },10); 

	$('body').on('click','.btn-save-ap',function(){
		var pos_id = $('#myModal').attr("data-modal-pos-id");
		var profile_id = $('#add_profile_id').val();
		// $('#myModal').modal('toggle');
		$('#myModal').modal('hide');
		$.ajax({
                  url: base_url + '/'+ secondLevelLocation +'/iisp_skills/ajax_profile_name',
                  data: {"iisp_profiles_id":profile_id},
                  dataType: 'json',
                  method:'POST',
	              	beforeSend: function() {
					    $('#response').html("<img src='http://spiffygif.com/?color=000&length=15&radius=10&width=4' class='loader'/>");
					},
                    success:function (response)
                    {
                    	var profiler_name = response.name;
                    	$('#profile-pos-id-'+pos_id).text(profiler_name.substring(0, 5));
                    	$('#profile-pos-id-'+pos_id).attr('title',profiler_name);
                    	$('#profile-pos-id-'+pos_id).addClass('btn-danger');
                    	$('#profile-pos-id-'+pos_id).removeClass('btn-default');
                    	$('#profile-pos-id-'+pos_id).addClass('remove-profile-class');
                    	$('#profile-pos-id-'+pos_id).removeClass('user-add-class');
                    	$('#profile-pos-id-'+pos_id).removeAttr('data-toggle','modal');
                    	$('#profile-pos-id-'+pos_id).removeAttr('data-target','#myModal');
                    },
                });
		// data-toggle="modal" data-target="#myModal"

		$.ajax({
                  url: base_url + '/'+ secondLevelLocation +'/iisp_skills/ajax_skills_profile_data/'+profile_id,
                  data: {"iisp_profiles_id":profile_id},
                  dataType: 'json',
                  method:'POST',
                  	  beforeSend: function() {
					    $('#response').html("<img src='http://spiffygif.com/?color=000&length=15&radius=10&width=4' class='loader'/>");
					  },
                    success:function (data)
                    {
                       	  $.each(data, function(key,val) {
	          					var score = val.score;
	          					var skillLevel = val.iisp_skills_id;
         					   $('#checkbox-skill-'+skillLevel + '-pos-' + pos_id).text(score); 
         					   $('#checkbox-skill-'+skillLevel + '-pos-' + pos_id).css("background-color", "green"); 
         					   $('#checkbox-skill-'+skillLevel + '-pos-' + pos_id).css("color", "white"); 
						  });
                    },
                });
	});

});
