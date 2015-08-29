jQuery(document).ready(function($) { 
	$("#edit-linked-activities").change(function(){
		//$(".linklist").append($("#edit-linked-activities").val());
		 if ($("#edit-linked-activities option:selected").hasClass('selected')){

		 } else {

		$(".linklist").append("<div style='background:#CCC;margin:5px; padding:5px;' id = 'remove"+$("#edit-linked-activities").val()+"'>"+$("#edit-linked-activities option:selected").text() + "<input type='hidden' name='activities[]' value='"+$("#edit-linked-activities").val()+"'><span style='textalign:right; float:right; clear:both;' onclick='removedom("+$("#edit-linked-activities").val()+")'>X</span></div>");
		$("#edit-linked-activities option:selected").addClass('selected');

        }
	

	})  
});

function removedom(id){
	jQuery('#remove'+id).remove();
}

