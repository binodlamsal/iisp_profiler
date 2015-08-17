<!-- <div class="row">
	<div class="col-md-6">
	<?php print drupal_render(drupal_get_form('profilerform_skill_settings_form')); ?>
	</div>
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
				<?php print drupal_render(drupal_get_form('profilerform_skill_settings_form')); ?>
			</div>
		</div>
	</div>
	
</div>

<form method="post" id="profile_settings_ga">
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
						<td>Title</td>
						<td style="text-algin:center">Advanced</td>
					</tr>
				</thead>
				<tbody>
				<?php foreach($user_form_field_info as $uffi) : ?>
					<tr>
						<td><?php echo $uffi->name; ?><td>
						<td style="text-algin:left"><input type="checkbox" name="advanced[<?php echo $uffi->id; ?>]" value="<?php echo $uffi->default_advanced; ?>" <?php if($uffi->default_advanced == 1) {echo "checked";} else {echo '';} ?>><td>
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
								<table id="goal-fields"><thead><tr><td>Title</td><td>Type</td><td>Advanced</td><td>Actions</td></tr></thead>
								<tbody></tbody>
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
								<table id="goal-fields-enter"><thead><tr><td>Title</td><td>Type</td><td>Advanced</td><td>Actions</td></tr></thead>
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
										<td><input type="checkbox" name="goal_advanced" id="goal_advance" value="1"></td>
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
								<table id="activity-fields"><thead><tr><td>Title</td><td>Type</td><td>Advanced</td><td>Actions</td></tr></thead>
								<tbody></tbody>
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
								<table id="activity-fields-enter"><thead><tr><td>Title</td><td>Type</td><td>Advanced</td><td>Actions</td></tr></thead>
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

<div class="save-ajax-form col-md-12 " style="magin-top:10px">
	<input type="submit" name="save_from" value="SAVE ALL SETTINGS" class="btn btn-default btn-submit-second">
</div>
</form>
