<?php 
global $base_url;

?>

<div class="row">
  <div class="col-md-12" style="border-radius:10px; border:1px solid #eaeaea;">
    <legend> <i class="fa fa-plane"></i> &nbsp; Take a Tour</legend>
    <br/>
    <br/>
    <br/>
    
     <div class="owl-carousel owl-theme owl-slider thumbnail">
          <div class="item">
        <img src="http://stability.nikadevs.com/sites/stability.nikadevs.com/files/styles/project_1126_470/public/work-img-BIG-2.jpg?itok=a-P8sP-k" width="1126" height="470" />      </div>
          <div class="item">
        <img src="http://stability.nikadevs.com/sites/stability.nikadevs.com/files/styles/project_1126_470/public/work-img-BIG-1.jpg?itok=hlcNIZp8" width="1126" height="470" />      </div>
          <div class="item">
        <img src="http://stability.nikadevs.com/sites/stability.nikadevs.com/files/styles/project_1126_470/public/work-img-BIG-3.jpg?itok=Gl8sPglA" width="1126" height="470" />      </div>
         <div class="item">
        <img src="http://stability.nikadevs.com/sites/stability.nikadevs.com/files/styles/project_1126_470/public/work-img-BIG-2.jpg?itok=a-P8sP-k" width="1126" height="470" />      </div>
          <div class="item">
        <img src="http://stability.nikadevs.com/sites/stability.nikadevs.com/files/styles/project_1126_470/public/work-img-BIG-1.jpg?itok=hlcNIZp8" width="1126" height="470" />      </div>
          <div class="item">
        <img src="http://stability.nikadevs.com/sites/stability.nikadevs.com/files/styles/project_1126_470/public/work-img-BIG-3.jpg?itok=Gl8sPglA" width="1126" height="470" />      </div>
      </div>

  </div>
</div>
<hr class="lg">
<div class="row">
  <div class="col-md-6" style="border-radius:10px; border:1px solid #eaeaea;">
    <legend><i class="fa fa-key"></i> &nbsp; Goals</legend>
    <br/>
    <br/>
    <br/>
    <div class="table-responsive"> 
    	<table class="table table-bordered table-striped">
    	 <thead> <tr> <th>Title</th> <th>Status</th></thead>
    	 <tbody> 
    	 	<?php foreach($goals_profiler as $goal) { 

                  $result = get_goals_individual_data($goal->id);
                  
                  $newarray = array();
		foreach($result as $res){
			$newarray[$res->iisp_field_settings_id] = $res;
		}
		
		if($newarray[6]->value == '1'){
			$status = "<span style='color:red'>Pending</span>";
		} else if($newarray[6]->value == '2'){
			$status = "<span style='color:#CCCC00'>In progress</span>";
		} else if($newarray[6]->value == '3'){
			$status = "<span style='color:green'>Complete</span>";
		}
    	 		?>

    	 	<tr> <td><?php echo l($newarray[3]->value, "iisp_profiler/goals/$goal->id/edit", array('attributes' => array('style' => 'color:black;'))) ?></td> <td><?php echo $status; ?></td></tr> 

    	 	<?php } ?>
    	 	<tr> <td colspan='2'><a class="btn-sm btn-success btn" href="<?php echo $base_url; ?>/iisp_profiler/goals" style='width:100%;'>View All Goals</a></td></tr> 
    	 </tbody> </table></div>
  </div>
  <div class="col-md-6" style="border-radius:10px; border:1px solid #eaeaea;">
    <hr class="visible-sm visible-xs lg" s>
    <legend><i class="fa fa-archive"></i>&nbsp; Activities</legend>
    <br/>
    <br/>
    <br/>

     <div class="table-responsive"> 
    	<table class="table table-bordered table-striped">
    	 <thead> <tr> <th>Title</th> <th>Status</th></thead>
    	 <tbody> 
    	 	<?php 
    	 	foreach($activities_profiler as $activity) { 

                  $result = get_activities_individual_data($activity->id);
                  
                  $newarray = array();
		foreach($result as $res){
			$newarray[$res->iisp_field_settings_id] = $res;
		}
		
		if($newarray[6]->value == '1'){
			$status = "<span style='color:red'>Pending</span>";
		} else if($newarray[6]->value == '2'){
			$status = "<span style='color:#CCCC00'>In progress</span>";
		} else if($newarray[6]->value == '3'){
			$status = "<span style='color:green'>Complete</span>";
		}
    	 		?>

    	 	<tr> <td><?php echo l($newarray[3]->value, "iisp_profiler/activities/$activity->id/edit", array('attributes' => array('style' => 'color:black;'))) ?></td> <td><?php echo $status; ?></td></tr> 

    	 	<?php } ?>
    	 	<tr> <td colspan='2'><a class="btn-sm btn-success btn" href="<?php echo $base_url; ?>/iisp_profiler/activities" style='width:100%;'>View All Activities</a></td></tr> 
    	 </tbody> </table></div>

  </div>
</div>