jQuery(document).ready(function($) {
	 $("#profile_settings_ga").validate();
	 // $('#activity_name').rules('remove');

	 var root = document.location.hostname;
	 var pathArray = window.location.pathname.split( '/' );
	 var secondLevelLocation = pathArray[1];
	 var base_url = 'http://'+root+'/'+ secondLevelLocation;

	//Start for goal fields

	var counter_goal = $('#goal-fields').find('tbody').children('tr').length;
	var counter_activity = $('#activity-fields').find('tbody').children('tr').length;
	$('body').on('click','#goal-add-button', function () {
		$('[name="goal_name"]').rules('add', { 
	        required: true,
	    });
	    $('#goal_type').rules('add', { 
	        required: true,
	    });
    // $('#Other_Form_Fields').rules('remove');        
    var validate=$('#profile_settings_ga').valid();
		// $("#profile_settings_ga").validate();
		if(validate){
			$('#goal_name').rules('remove');
		    $('#goal_type').rules('remove');
		      

			var goal_name = $("#goal_name").val();
			var goal_type = $("#goal_type").val();
			var goal_advance = $("#goal_advance").attr("checked") ? 1 : 0;
			//Start removing the fields
			$("#goal_name").val('');
			$("#goal_type").val('');
			$("#goal_advance").attr("checked" ,false);
			// End removing the fields$('#myTable').find('tbody:last')
			$("#goal-fields").find('tbody:last').append('<tr><td><div class="form-group"><input type="text" name="goal_name_set['+counter_goal+']" class="form-control" value="'+goal_name+'" id="goal_name'+counter_goal+'" required></div></td><td>'+goal_type+'<input type="hidden" name="goal_type_set['+counter_goal+']" value="'+goal_type+'" required></td><td><input type="checkbox" name="goal_advanced['+counter_goal+']"'+(goal_advance==1? 'checked ' : '')+'id="advance['+counter_goal+']" value="'+goal_advance+'"></td><td><input type="button" value="Remove" class="btn-sm btn-danger btn-remove" id="goal-remove-button['+counter_goal+']"></td></tr>');

			counter_goal++;
		}
	});

	$('body').on('click','.btn-remove', function () {
		 $(this).closest("tr").remove();
	});
	//End for goal fields

	//Start for activity fields
	$('body').on('click','#activity-add-button', function () {
		$('[name="activity_name"]').rules('add', { 
	        required: true,
	    });
	    $('#activity_type').rules('add', { 
	        required: true,
	    });

    	var validate=$('#profile_settings_ga').valid();
		if(validate){
			$('#activity_name').rules('remove');
		    $('#activity_type').rules('remove');
				var activity_name = $("#activity_name").val();
				var activity_type = $("#activity_type").val();
				var activity_advance = $("#activity_advance").attr("checked") ? 1 : 0;

				//Start removing the fields
				$("#activity_name").val('');
				$("#activity_type").val('');
				$("#activity_advance").attr("checked" ,false);
				//End removing the fields
				$("#activity-fields").find('tbody:last').append('<tr><td><div class="form-group"><input type="text" name="activity_name_set['+counter_activity+']" class="form-control" value="'+activity_name+'" id="activity_name'+counter_activity+'"></div></td><td>'+activity_type+'<input type="hidden" name="activity_type_set['+counter_activity+']" value="'+activity_type+'"></td><td><input type="checkbox" name="activity_advanced['+counter_activity+']"'+(activity_advance==1? 'checked ' : '')+'id="advance['+counter_activity+']" value="'+activity_advance+'"></td><td class="btn"><input type="button" value="Remove" class="btn-sm btn-danger btn-remove" id="activity-remove-button['+counter_activity+']"></td></tr>');

			counter_activity++;
		}
	});

	$('body').on('click','.btn-remove', function () {
		 $(this).closest("tr").remove();
	});
	//End for goal fields

	
	$('body').on('click','.checkboxes', function () {
		 if($(this).attr("checked") == "checked"){
		 	$(this).val(1);
		 }else{
		 	$(this).val(0);
		 }
	});
});

