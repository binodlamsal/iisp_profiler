<?php 
global $base_url;
$form = drupal_get_form('profilerform_skill_settings_form');
?>
	<!--</div>
</div> -->
<?php //var_dump($user_form_field_info);die; ?>

<div class="panel-group col-md-8" id="accordion">
	<div class="panel panel-default">
		<div class="panel-heading">
			<h4 class="panel-title">
				<a data-toggle="collapse" data-parent="#accordion" href="#accordion-1">
					Settings
				</a>
			</h4>
		</div>
		<div id="accordion-1" class="panel-collapse collapse in">
			<div class="panel-body">
				<?php print drupal_render($form); ?>
			</div>
		</div>
	</div>
	
</div>

<form method="post" id="profile_settings_ga" action="<?php echo $base_url; ?>/?q=skills/receive_settings_data">
<div class="tabs col-md-12" style="margin-top:30px">
  <ul class="nav nav-tabs">
	<li class="active"><a href="#tab-1" data-toggle="tab">System Attribute Settings</a></li>
	<li><a href="#tab-2" data-toggle="tab">User Defined Goal Fields</a></li>
	<li><a href="#tab-3" data-toggle="tab">User Defined Activity Fields</a></li>
  </ul>
    <div class="tab-content">
    	<div class="tab-pane fade  active in" id="tab-1">
			<p>When recording your Development Goals and Activities, there will be fields you use often (standard fields) and others you only use from time to time (advanced fields). To make using BCS Personal Development Plan quicker and easier to use, at any time you can make the fields you use less often into Advanced fields</p>
			<table>
				<thead>
					<tr>
						<th>Title</th>
						<th >Advanced</th>
					</tr>
				</thead>
				<tbody>
				<?php foreach($user_form_field_info as $uffi) : ?>
				<?php 	
					$user_system_attribute_form_fields = user_system_attribute_form_fields($uffi->id);
					if($user_system_attribute_form_fields){
						$default_advanced = $user_system_attribute_form_fields->advanced;
				    }else{
					    $default_advanced = $uffi->default_advanced;
			     	} 
			     ?>
					<tr>
						<td><?php echo $uffi->name; ?></td>
						<td ><input type="checkbox" class="checkboxes" name="advanced[<?php echo $uffi->id; ?>]" value="<?php echo $default_advanced; ?>" <?php if($default_advanced == 1) {echo "checked";} else {echo '';} ?>><td>
					</tr>
				<?php endforeach; ?>
				</tbody>
			</table>
		</div>
		<div class="tab-pane fade " id="tab-2">
			<p>Make BCS Personal Development Plan even more personal to you by creating your own customised fields within your Development Goals. Give the field a name, choose a type and identify if it is a field you will use regularly or (if not) tick it as an Advanced field to place it into the Advanced fields area.</p>		
			
			<div class="panel-group col-md-12" id="accordion">
				<div class="panel panel-default">
					<div class="panel-heading">
						<h4 class="panel-title">
							<a data-parent="#accordion" href="#accordion-1">
								Goal Defined fields
							</a>
						</h4>
					</div>
					<div id="accordion-1" class="panel-collapse collapse in">
						<div class="panel-body">
							<div class="append-goals">
								<table id="goal-fields"><thead><tr><th>Title</th><th>Type</th><th>Advanced</th><th>Actions</th></tr></thead>
								<tbody>
									<?php 	
										$user_goal_form_fields = user_goal_form_fields();
								     	foreach ($user_goal_form_fields as $key => $goal_fields) { ?>
										   	<tr>
												<td><div class="form-group"><input type="text" name="goal_name_set[<?php echo $key; ?>]" class="form-control" value="<?php echo $goal_fields->title; ?>" id="goal_name<?php echo $key; ?>"></div></td>
												<td>
													<?php echo $goal_fields->type; ?><input type="hidden" name="goal_type_set[<?php echo $key; ?>]" value="<?php echo $goal_fields->type; ?>">
												</td>
												<td><input type="checkbox" name="goal_advanced[<?php echo $key; ?>]" id="goal_advance<?php echo $key; ?>" value="<?php echo $goal_fields->advanced; ?>" <?php if($goal_fields->advanced == 1){echo "checked";} ?>></td>
												<td><input type="button" value="Remove" class="btn-sm btn-danger btn-remove" id="goal-remove-button[<?php echo $key; ?>]"></td>
											</tr>
								     	
								    <?php } ?>
								</tbody>
								</table>
							</div>
						</div>
					</div>
				</div>
				
			</div>

			<div class="panel-group col-md-12" id="accordion" style="margin-top:25px;">
				<div class="panel panel-default">
					<div class="panel-heading">
						<h4 class="panel-title">
							<a data-parent="#accordion" href="#accordion-1">
								Add new goal fields
							</a>
						</h4>
					</div>
					<div id="accordion-1" class="panel-collapse collapse in">
						<div class="panel-body">
							<div class="goals-enter">
								<table id="goal-fields-enter"><thead><tr><th>Title</th><th>Type</th><th>Advanced</th><th>Actions</th></tr></thead>
								<tbody>
									<tr>
										<td><div class="form-group"><input type="text" name="goal_name" class="form-control" value="" id="goal_name"></div></td>
										<td>
											<div class="form-group form-type-select">
											<select name="goal_type" class="form-select form-control" id="goal_type">
												<option value="">Select</option>
												<option value="textfield">Text</option>
												<option value="int">Numerical</option>
												<option value="date">Date</option>
												<option value="decimal">Decimal</option>
											</select>
											</div>
										</td>
										<td><input type="checkbox" name="goal_advance" id="goal_advance" value="1"></td>
										<td><input type="button" value="Add" class="btn-sm btn-success btn" id="goal-add-button"></td>
									</tr>
								</tbody>
								</table>
							</div>	
						</div>
					</div>
				</div>
				
			</div>
		</div>
		<div class="tab-pane fade " id="tab-3">
			<p>Make BCS Personal Development Plan even more personal to you by creating your own customised fields within your Development Goals. Give the field a name, choose a type and identify if it is a field you will use regularly or (if not) tick it as an Advanced field to place it into the Advanced fields area.</p>		
			
			<div class="panel-group col-md-12" id="accordion">
				<div class="panel panel-default">
					<div class="panel-heading">
						<h4 class="panel-title">
							<a data-parent="#accordion" href="#accordion-1">
								Activity Defined Fields
							</a>
						</h4>
					</div>
					<div id="accordion-1" class="panel-collapse collapse in">
						<div class="panel-body">
							<div class="append-activity">
								<table id="activity-fields">
                                <thead><tr><th>Title</th><th>Type</th><th>Advanced</th><th>Actions</th></tr></thead>
								<tbody>
									<?php 	
										$user_activity_form_fields = user_activity_form_fields();
								     	foreach ($user_activity_form_fields as $key => $activity_fields) { ?>
										   	<tr>
												<td><div class="form-group"><input type="text" name="activity_name_set[<?php echo $key; ?>]" class="form-control" value="<?php echo $activity_fields->title; ?>" id="activity_name<?php echo $key; ?>"></div></td>
												<td>
													<?php echo $activity_fields->type; ?><input type="hidden" name="activity_type_set[<?php echo $key; ?>]" value="<?php echo $activity_fields->type; ?>">
												</td>
												<td><input type="checkbox" name="activity_advanced[<?php echo $key; ?>]" id="activity_advance<?php echo $key; ?>" value="<?php echo $activity_fields->advanced; ?>" <?php if($activity_fields->advanced == 1){echo "checked";} ?>></td>
												<td><input type="button" value="Remove" class="btn-sm btn-danger btn-remove" id="activity-remove-button[<?php echo $key; ?>]"></td>
											</tr>
								     	
								    <?php } ?>
								</tbody>
								</table>
							</div>
						</div>
					</div>
				</div>
				
			</div>

			<div class="panel-group col-md-12" id="accordion" style="margin-top:25px;">
				<div class="panel panel-default">
					<div class="panel-heading">
						<h4 class="panel-title">
							<a data-parent="#accordion" href="#accordion-1">
								Add new activity fields
							</a>
						</h4>
					</div>
					<div id="accordion-1" class="panel-collapse collapse in">
						<div class="panel-body">
							<div class="activitys-enter">
								<table id="activity-fields-enter"><thead><tr><th>Title</th><th>Type</th><th>Advanced</th><th>Actions</th></tr></thead>
								<tbody>
									<tr>
										<td><div class="form-group"><input type="text" name="activity_name" class="form-control" value="" id="activity_name"></div></td>
										<td>
											<div class="form-group form-type-select">
											<select name="activity_type" class="form-select form-control" id="activity_type">
												<option value="">Select</option>
												<option value="textfield">Text</option>
												<option value="int">Numerical</option>
												<option value="date">Date</option>
												<option value="decimal">Decimal</option>
											</select>
											</div>
										</td>
										<td><input type="checkbox" name="activity_advanced" id="activity_advance" value="1"></td>
										<td><input type="button" value="Add" class="btn-sm btn-success btn" id="activity-add-button"></td>
									</tr>
								</tbody>
								</table>
							</div>	
						</div>
					</div>
				</div>
				
			</div>
		</div>
	</div>
</div>

<div class="save-ajax-form col-md-12 " style="margin-top:20px">
	<input type="submit" name="save_from" value="SAVE ALL SETTINGS" class="btn btn-default btn-submit-second">
</div>
</form>
