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
function sifa_skill_types($tab = '') {
  $output = '';
  $build['sifa_skill_types_settings_create'] = drupal_get_form('sifa_skill_types_settings_form');
	$output = drupal_render($build);
  return $output;
}

function sifa_skill_types_settings_form($form, &$form_state, $sifa_skill_types_settings = NULL){
	$form = array();
	$form['#attributes']['class'][] = 'inform';
	
  //Start checking if previously stored skill types for sfia
  $sifa_skill_types_settings = db_select('iisp_sifaplus_skill_types', 'fs')
            ->fields('fs')
            ->condition('fs.id', 1)
            ->execute()
            ->fetchObject();
  //End checking if previously stored skill types for sfia


	$weight = 0;
	if(!empty($sifa_skill_types_settings)){
	$skill_types = $sifa_skill_types_settings->name;
  $form['id'] = array(
  		'#type' => 'hidden',
  		'#value' =>$sifa_skill_types_settings->id,
	  );	

	} else {
        $skill_types    =  "";
	}
	
	
  $form['name'] = array(
    '#type' => 'textarea',
    '#title' => t('Role Family'),
  	'#required' => true,
  	'#weight' => $weight++,
  	'#default_value' => $skill_types,
    '#description' => t('Add key|value pair for skill types. Eg: 0|Animation Development, 1|Application Support, 2|Asset Management etc, please enter one per line.')
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save skill settings'),
      '#weight' => $weight++,
	  '#prefix' => '<div class="form-item form-actions">',
	  '#suffix' => '</div>',
      '#submit' => array('sifa_skill_types_settings_form_submit'),
  );
  
  return $form;
	
}

function sifa_skill_types_settings_form_submit($form, &$form_state){
	global $user;
  $sifa_skill_types_settings = (object) $form_state['values'];
	$sifa_skill_types_settings->name = trim($sifa_skill_types_settings->name);
	if(empty($sifa_skill_types_settings->id)){
		drupal_write_record('iisp_sifaplus_skill_types', $sifa_skill_types_settings);
	} else {
		drupal_write_record('iisp_sifaplus_skill_types', $sifa_skill_types_settings, 'id');
	}

	drupal_set_message('Sifa plus skill types saved');
	$form_state['redirect'] = 'admin/iisp_profiler/sifa_skills_types';
}


