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
  $output = '';
  $build['profilerform_skill_settings_create'] = drupal_get_form('profilerform_skill_settings_form');
  $build['system_attribute_settings_create'] = drupal_get_form('system_attribute_settings_form');
	$output = drupal_render($build);
  return $output;
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
		    '#title' => t('Select skill types'),
		  	'#required' => true,
		  	'#weight' => $weight++,
		  	'#default_value' => $iisp_sifaplus_skill_types_id,
		  	'#options' => $options_skill_types,
		    '#description' => t('Tips and Info : Please indentify which of the SFIAplus skills best matches your primary specialism. This will help us provide you with relevant content and messages to help you with your CPD.'),
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
		$default_advanced = $sys_ff->default_advanced;
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
	foreach ($system_attribute_settings as $key => $iisp_field_settings) {
		print_r($key);
		print_r($iisp_field_settings[1]);
		die;
		$check_if_user_has_attribute_settings = check_if_user_has_profile_settings('isp_field_user_data', 'as', 'uid',$user->uid, 'id');
		if($check_if_user_has_attribute_settings){
			$saved_system_attribute_settings = drupal_write_record('isp_field_user_data', $system_attribute_settings, 'id');
		}else{
			$saved_system_attribute_settings = drupal_write_record('isp_field_user_data', $system_attribute_settings);
		}
	}
	if(empty($system_attribute_settings->id)){
		$saved_system_attribute_settings = drupal_write_record('iisp_user_settings', $system_attribute_settings);
	} else {
		$saved_system_attribute_settings = drupal_write_record('iisp_user_settings', $system_attribute_settings, 'id');
	}
	if($saved_system_attribute_settings){
		$message = 'User skill settings saved';
		drupal_set_message('User skill settings saved');
	}else{
		$message = 'Problems in saving user skill settings';
		drupal_set_message('Problems in saving user skill settings');
	}
//Start for saved message
  $selector = '#system_saved_message';
  $commands = array();
  // $commands[] = ajax_command_after($selector, "New 'after'...");
  $commands[] = ajax_command_replace($selector, "<div id='".$selector."'>".$message."</div>");
  return array('#type' => 'ajax', '#commands' => $commands);
//End for saved message

}





