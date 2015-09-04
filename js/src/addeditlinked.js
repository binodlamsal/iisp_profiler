jQuery(document).ready(function($) { 
	$("#edit-linked-activities").change(function(){
		//$(".linklist").append($("#edit-linked-activities").val());
		 if ($("#edit-linked-activities option:selected").hasClass('selected')){

		 } else {

		$(".linklist").append("<div style='width:100%; background:#CCC;margin:5px; padding:5px;' class='btn btn-small btn-default' id = 'remove"+$("#edit-linked-activities").val()+"'><a href= '#'>"+$("#edit-linked-activities option:selected").text() + "</a><input type='hidden' name='activities[]' value='"+$("#edit-linked-activities").val()+"'><span style='textalign:right; margin-right:10px; float:right; clear:both;' onclick='removedom("+$("#edit-linked-activities").val()+")'>X</span></div>");
		$("#edit-linked-activities option:selected").addClass('selected');

        }
	

	})  
});

function removedom(id){
	jQuery('#remove'+id).remove();
}

