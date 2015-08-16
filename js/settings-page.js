jQuery(document).ready(function($) {
	var counter=0;
	$('body').on('click','#goal-add-button', function () {
		debugger;
		var name = $("#goal_name").val();
		var type = $("#goal_type").val();
		var advance = $("#advance").attr("checked") ? 1 : 0;
		$("#goal-fields").find('tbody').append('<tr><td><div class="form-group"><input type="text" name="goal_name_set['+counter+']" class="form-control" value="'+name+'" id="goal_name'+counter+'"></div></td><td>'+type+'</td><td><input type="checkbox" name="goal_advanced['+counter+']"'+(advance==1? 'checked ' : '')+'id="advance['+counter+']" value="'+advance+'"></td><td class="btn"><input type="button" value="Remove" class="btn-sm btn-danger btn-remove" id="goal-remove-button['+counter+']"></td>');
		    
		    // .append('<td><div class="form-group"><input type="text" name="goal_name_set['+counter+']" class="form-control" value="'+name+'" id="goal_name'+counter+'"></div></td>')
		    // .append('<td>'+type+'</td>')
		    // .append('<td><input type="checkbox" name="goal_advanced['+counter+']"'+(advance==1? 'checked ' : '')+'id="advance['+counter+']" value="'+advance+'"></td>')
		    // .append('<td class="btn"><input type="button" value="Remove" class="btn-sm btn-danger btn " id="goal-remove-button['+counter+']"></td>')
		    
		                
		   
	counter++;
	});

	$('body').on('click','.btn-remove', function () {
		debugger;
		 $(this).closest("tr").remove();
	});
});

