<?php

/**
 *
 * Admin page sifa skill types setting
 * 
 */
// Add all forms definitions

//
// sifa skill types setting form
//
function iisp_profiler_settings() {
	global $base_url;
	global $user;
	$path = drupal_get_path('module', 'iisp_profiler');
	drupal_add_js($base_url . '/' . $path . '/js/jquery.validate.min.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2000));
	drupal_add_js($base_url . '/' . $path . '/js/noslider.min.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2010));
	drupal_add_js($base_url . '/' . $path . '/js/settings-page.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2500));
    
	
	drupal_add_css($base_url . '/' . $path . '/css/nouislider.pips.css', array('type' => 'external', 'weight' => '600'));
        

	//Start get previously store user skill settings for the specific user id	
	  $system_attribute_form_fields = db_select('iisp_field_settings', 'fs')
	            ->fields('fs')
	            // ->condition('fs.uid',$user->uid)
				->orderBy('fs.weight', 'ASC')
	            ->execute()
	            ->fetchALL();
	  //End get previously store user skill settings for the specific user id

	   // //Start get previously fetched user skill settings of user id
	  	// $user_system_attribute_form_fields = db_select('iisp_field_user_data', 'ud')
    //     ->fields('ud')
    //     ->condition('ud.uid',$user->uid)
    //     ->condition('ud.iisp_field_settings_id',$sys_ff->id)
    //     ->execute()
    //     ->fetchobject();
	   // //End get previously fetched user skill settings of user id

	return theme('profiler_settings_page', array('user_form_field_info' => $system_attribute_form_fields));	  
}

function profilerform_skill_settings_form($form, &$form_state, $profilerform_skill_settings = NULL){
	global $user;
	$form = array();
	$form['#attributes']['class'][] = 'inform';
	  //Start get previously store user skill settings for the specific user id	
	  $profilerform_skill_settings = db_select('iisp_user_settings', 'ius')
	            ->fields('ius')
	            ->condition('ius.uid',$user->uid)
	            ->execute()
	            ->fetchObject();
	  //End get previously store user skill settings for the specific user id	
	  
	  //Start get previously stored skill types for sfia
	  $skill_types_fields = db_select('iisp_sifaplus_skill_types', 'fs')
	            ->fields('fs')
	            ->execute()
	            ->fetchAll();
	  $options_skill_types = get_keyvalue_array($skill_types_fields[0]->name);
	  // End get previously stored skill types for sfia

	  //Start get previously stored skill types for sfia
	  $skill_levels_fields = db_select('iisp_sifaplus_skill_levels', 'fs')
	            ->fields('fs')
	            ->execute()
	            ->fetchAll();
	  $options_skill_levels = get_keyvalue_array($skill_levels_fields[0]->name);
	  // End get previously stored skill types for sfia


	$weight = 0;
	if(!empty($profilerform_skill_settings)){
	$cpd_year_start = $profilerform_skill_settings->cpd_year_start;
	$primary_sifaplus_level = $profilerform_skill_settings->primary_sifaplus_level;
	$iisp_sifaplus_skill_types_id = $profilerform_skill_settings->iisp_sifaplus_skill_types_id;
  	$form['id'] = array(
  		'#type' => 'hidden',
  		'#value' =>$profilerform_skill_settings->id,
	  );	

	} else {
        $cpd_year_start    = '';
        $iisp_sifaplus_skill_types_id    =  "";
        $primary_sifaplus_level    =  "";
	}
	
		$form['cpd_year_start'] = array(
		    '#type' => 'date_popup',
		    '#title' => t('CPD Year Start Date'),
		    '#weight' => $weight++,
		    '#date_format' => 'Y-m-d',
		    '#default_value' => $cpd_year_start,
		    '#validate' => 'required',
		    '#description' => t('Tips and Info : This is the day and month your review year starts; this may match that of your employer. If you are unsure, enter 01/01/2015.'),
	  	);

	  	$form['iisp_sifaplus_skill_types_id'] = array(
		    '#type' => 'select',
		    '#title' => t('Select role family'),
		  	'#required' => true,
		  	'#weight' => $weight++,
		  	'#default_value' => $iisp_sifaplus_skill_types_id,
		  	'#options' => $options_skill_types,
		    '#description' => t('Tips and Info : Please indentify which of the SFIAplus skills best matches your primary specialism. This will help us provide you with relevant content and messages to help you with your CPD.'),
			'#select2' => array(
			  'width' => '200',
			  'placeholder' => t('Select categories'),
			  'allowClear'   => TRUE,
			  'minimumResultsForSearch' => '1',
			),
		  );

		$form['primary_sifaplus_level'] = array(
		    '#type' => 'select',
		    '#title' => t('Select skill level'),
		  	'#required' => true,
		  	'#weight' => $weight++,
		  	'#default_value' => $primary_sifaplus_level,
		  	'#options' => $options_skill_levels,
		    '#description' => t('Tips and Info : Please use the slider to identify the closest fit to your current level in the IT Profession. This will help us provide you with relevant content and messages to help you with your CPD.')
		  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save all settings'),
      '#weight' => $weight++,
	  '#prefix' => '<div class="form-item form-actions">',
	  '#suffix' => '</div><div id="saved_message"></div>',
      '#ajax' => array(
        'callback' => 'profilerform_skill_settings_form_submit',
        'wrapper' => 'profilerform_skill_settings_form',
        'method' => 'replace',
        'effect' => 'fade',
      ),
  );
  
  return $form;
}

function profilerform_skill_settings_form_submit($form, &$form_state){
	global $user;
	$profilerform_skill_settings = (object) $form_state['values'];
	$profilerform_skill_settings->uid = $user->uid;
	if(empty($profilerform_skill_settings->id)){
		$saved_profilerform_skill_settings = drupal_write_record('iisp_user_settings', $profilerform_skill_settings);
	} else {
		$saved_profilerform_skill_settings = drupal_write_record('iisp_user_settings', $profilerform_skill_settings, 'id');
	}
	if($saved_profilerform_skill_settings){
		$message = 'User skill settings saved';
		drupal_set_message('User skill settings saved');
	}else{
		$message = 'Problems in saving user skill settings';
		drupal_set_message('Problems in saving user skill settings');
	}
//Start for saved message
  $selector = '#saved_message';
  $commands = array();
  // $commands[] = ajax_command_after($selector, "New 'after'...");
  $commands[] = ajax_command_replace($selector, "<div id='".$selector."'>".$message."</div>");
  return array('#type' => 'ajax', '#commands' => $commands);
//End for saved message

}

function system_attribute_settings_form($form, &$form_state, $system_attribute_settings = NULL){
	global $user;
	$form = array();
	$form['#attributes']['class'][] = 'inform';
	  //Start get previously store user skill settings for the specific user id	
	  $system_attribute_form_fields = db_select('iisp_field_settings', 'fs')
	            ->fields('fs')
	            // ->condition('fs.uid',$user->uid)
	            ->execute()
	            ->fetchALL();
	  //End get previously store user skill settings for the specific user id	
	  

	$weight = 0;
	if(!empty($system_attribute_settings)){
	$cpd_year_start = $system_attribute_settings->cpd_year_start;
	$primary_sifaplus_level = $system_attribute_settings->primary_sifaplus_level;
	$iisp_sifaplus_skill_types_id = $system_attribute_settings->iisp_sifaplus_skill_types_id;
  	$form['id'] = array(
  		'#type' => 'hidden',
  		'#value' =>$system_attribute_settings->id,
	  );	

	} else {
        $cpd_year_start    = '';
	}
	
	foreach($system_attribute_form_fields as $sys_ff){
	  $user_system_attribute_form_fields = db_select('iisp_field_user_data', 'ud')
        ->fields('ud')
        ->condition('ud.uid',$user->uid)
        ->condition('ud.iisp_field_settings_id',$sys_ff->id)
        ->execute()
        ->fetchobject();
      if($user_system_attribute_form_fields){
		$default_advanced = $user_system_attribute_form_fields->advanced;
      }else{
		$default_advanced = $sys_ff->default_advanced;
      }

	  	$form['iisp_field_settings_id'][$sys_ff->id] = array(
		    '#type' => 'checkboxes',
		    '#title' => t($sys_ff->name),
		  	'#options' => array(1 => ''),
		  	'#weight' => $sys_ff->weight,
		    '#default_value' => array($sys_ff->id=>$default_advanced),
		  );
	 }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save all settings'),
      '#weight' => $weight++,
	  '#prefix' => '<div class="form-item form-actions">',
	  '#suffix' => '</div><div id="system_saved_message"></div>',
      '#ajax' => array(
        'callback' => 'system_attribute_settings_form_submit',
        'wrapper' => 'system_attribute_settings_form',
        'method' => 'replace',
        'effect' => 'fade',
      ),
  );

  return $form;
}

function system_attribute_settings_form_submit($form, &$form_state){
	global $user;
	$system_attribute_settings = (object) $form_state['values'];
	$form_submit = $system_attribute_settings->submit;
	$form_build_id = $system_attribute_settings->form_build_id;
	$form_token = $system_attribute_settings->form_token;
	$form_id = $system_attribute_settings->form_id;
	$op = $system_attribute_settings->op;
	unset($system_attribute_settings->submit);
	unset($system_attribute_settings->form_build_id);
	unset($system_attribute_settings->form_token);
	unset($system_attribute_settings->form_id);
	unset($system_attribute_settings->op);

	foreach ($system_attribute_settings as $key => $iisp_field_settings) {
		$check_if_user_has_attribute_settings = check_if_user_has_profile_settings($key,$user->uid);
		if($check_if_user_has_attribute_settings){

			$saved_system_attribute_settings = db_update('iisp_field_user_data')
												  ->fields(array(
												    'advanced' => $iisp_field_settings[1],
												    'uid' => $user->uid,
												  ))
												  ->condition('uid', $user->uid)
												  ->condition('iisp_field_settings_id',$key)
												  ->execute();
		}else{
			$saved_system_attribute_settings =  db_insert('iisp_field_user_data') 
														->fields(array(
														  'uid' => $user->uid,
														  'advanced' => $iisp_field_settings[1],
														  'iisp_field_settings_id' => $key,
														))
														->execute();
		}
	}

	$message = '<div class="alert alert-dismissable alert-success">
<button type="button" class="close" data-dismiss="alert">×</button><h2 class="element-invisible">Status message</h2>
 <ul><li>User skill settings saved</li></ul></div>';
	$system_attribute_settings->submit = $form_submit;
	$system_attribute_settings->form_build_id = $form_build_id;
	$system_attribute_settings->form_token =$form_token;
	$system_attribute_settings->form_id =$form_id;
	$system_attribute_settings->op = $op;

	//Start for saved message
	  $selector = '#system_saved_message';
	  $commands = array();
	  $commands[] = ajax_command_replace($selector, "<div id='".$selector."'>".$message."</div>");
	  return array('#type' => 'ajax', '#commands' => $commands);
	//End for saved message


}


function receive_settings_data(){
	global $user;

	db_delete('iisp_field_user_data')->condition('uid',$user->uid)->execute();
	if($_POST['edit-goal-id']){
		 db_delete('iisp_goals_custom_fields')->condition('id', $_POST['edit-goal-id'], 'NOT IN')->condition('uid',$user->uid)->execute();
	}else{
		 db_delete('iisp_goals_custom_fields')->condition('uid',$user->uid)->execute();
	}
	if($_POST['edit-activity-id']){
		 db_delete('iisp_activities_custom_fields')->condition('id', $_POST['edit-activity-id'], 'NOT IN')->condition('uid',$user->uid)->execute();
	}else{
		 db_delete('iisp_activities_custom_fields')->condition('uid',$user->uid)->execute();
	}

 //End delete the previous data from issp_field_user_data
  if(isset($_POST['advanced'])){
   //Fields user settings 
  foreach ($_POST['advanced'] as $field_settings_id => $value) {
    $data_field_user_data = (object) array(
      'uid' => $user->uid,
      'advanced' => $value,
      'iisp_field_settings_id' => $field_settings_id,
     );
    drupal_write_record('iisp_field_user_data',$data_field_user_data);
  }
 }

 if(isset($_POST['goal_name_set'])){
  //Fields goal_settings 
  foreach ($_POST['goal_name_set'] as $key => $goal_name){
   if(isset($_POST['edit-goal-id'][$key])){
    $data_field_goal_data = (object) array(
      'id' => $_POST['edit-goal-id'][$key],
      'title' => $goal_name,
      'type' => isset($_POST['goal_type_set'][$key]) ? $_POST['goal_type_set'][$key] : '',
      'advanced' => isset($_POST['goal_advanced'][$key]) ? $_POST['goal_advanced'][$key] :  0,
      'uid' => $user->uid,
     );
    drupal_write_record('iisp_goals_custom_fields',$data_field_goal_data,'id');
   }else{
    $data_field_goal_data = (object) array(
      'title' => $goal_name,
      'type' => isset($_POST['goal_type_set'][$key]) ? $_POST['goal_type_set'][$key] : '',
      'advanced' => isset($_POST['goal_advanced'][$key]) ? $_POST['goal_advanced'][$key] :  0,
      'uid' => $user->uid,
     );
    drupal_write_record('iisp_goals_custom_fields',$data_field_goal_data);
   }
  }
 }

 if(isset($_POST['activity_name_set'])){
    foreach ($_POST['activity_name_set'] as $key => $activity_name){
   if(isset($_POST['edit-activity-id'][$key])){
     $data_field_activity_data = (object) array(
      'id' => $_POST['edit-activity-id'][$key],
      'title' => $activity_name,
      'type' => isset($_POST['activity_type_set'][$key]) ? $_POST['activity_type_set'][$key] : '',
      'advanced' => isset($_POST['activity_advanced'][$key]) ? $_POST['activity_advanced'][$key] :  0,
      'uid' => $user->uid,
     );
     drupal_write_record('iisp_activities_custom_fields',$data_field_activity_data,'id');
   }
   else{
     $data_field_activity_data = (object) array(
      'title' => $activity_name,
      'type' => isset($_POST['activity_type_set'][$key]) ? $_POST['activity_type_set'][$key] : '',
      'advanced' => isset($_POST['activity_advanced'][$key]) ? $_POST['activity_advanced'][$key] :  0,
      'uid' => $user->uid,
     );
     drupal_write_record('iisp_activities_custom_fields',$data_field_activity_data);
   }  
    }
 }
 drupal_set_message('Congratulations!, Saving the settings data becomes successfull.');
 drupal_goto('iisp_profiler/settings');

	
}