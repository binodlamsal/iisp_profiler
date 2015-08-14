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
	$output = drupal_render($build);
  return $output;
}

function profilerform_skill_settings_form($form, &$form_state, $profilerform_skill_settings = NULL){
	global $user;
	$form = array();
	$form['#attributes']['class'][] = 'inform';
	
	  //Start get previously stored skill types for sfia
	  $skill_types_fields = db_select('iisp_sifaplus_skill_types', 'fs')
	            ->fields('fs')
	            ->execute()
	            ->fetchAll();
	  $options = get_keyvalue_array($skill_types_fields[0]->name);
	  // End get previously stored skill types for sfia

	  //Start get previously stored skill types for sfia
	  $skill_levels_fields = db_select('iisp_sifaplus_skill_levels', 'fs')
	            ->fields('fs')
	            ->execute()
	            ->fetchAll();
	  $options = get_keyvalue_array($skill_levels_fields[0]->name);
	  print_r($options),
	  // End get previously stored skill types for sfia


	$weight = 0;
	if(!empty($profilerform_skill_settings)){
	$skill_types = $profilerform_skill_settings->name;
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
		  	'#options' => array(),
		    '#description' => t('Tips and Info : Please indentify which of the SFIAplus skills best matches your primary specialism. This will help us provide you with relevant content and messages to help you with your CPD.'),
		  );

		$form['primary_sifaplus_level'] = array(
		    '#type' => 'select',
		    '#title' => t('Select skill level'),
		  	'#required' => true,
		  	'#weight' => $weight++,
		  	'#default_value' => $primary_sifaplus_level,
		  	'#options' => array(),
		    '#description' => t('Tips and Info : Please use the slider to identify the closest fit to your current level in the IT Profession. This will help us provide you with relevant content and messages to help you with your CPD.')
		  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save sifa skill types'),
      '#weight' => $weight++,
    '#prefix' => '<div class="form-item form-actions">',
    '#suffix' => '</div>',
      '#submit' => array('profilerform_skill_settings_form_submit'),
  );
  
  return $form;
}

function profilerform_skill_settings_form_submit($form, &$form_state){
	global $user;
	$profilerform_skill_settings = (object) $form_state['values'];
	$profilerform_skill_settings->default_advanced = $profilerform_skill_settings->default_advanced[1];
	if(empty($profilerform_skill_settings->id)){
		drupal_write_record('iisp_sifaplus_skill_types', $profilerform_skill_settings);
	} else {
		drupal_write_record('iisp_sifaplus_skill_types', $profilerform_skill_settings, 'id');
	}

	drupal_set_message('IISP sifa plus skill types saved');
	$form_state['redirect'] = 'admin/iisp_skills/sifa_skills_types';
}


