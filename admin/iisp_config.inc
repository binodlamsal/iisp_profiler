<?php

function iisp_admin_config_form($form, $form_state){
  $form = array();

  $form['application_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of the application'),
    '#default_value' => variable_get('application_name'),
    '#description' => t("Please enter the name of the application example:IISP Profiler"),
    '#required' => TRUE,
  );
  
  $form['iisp_skiller_role_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the IISP skiller role id(numeric value)'),
    '#default_value' => variable_get('iisp_skiller_role_id'),
	'#element_validate' => array('element_validate_number'),
    '#description' => t("Please enter the IISP skiller role id in number"),
    '#required' => TRUE,
  );
  
  $form['iisp_skill_manager_role_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the skill manager role id(numeric value)'),
    '#default_value' => variable_get('iisp_skill_manager_role_id'),
	'#element_validate' => array('element_validate_number'),
    '#description' => t("Please enter the skill manager role id in number"),
    '#required' => TRUE,
  );
  
  $form['iisp_skiller_compare_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of profilers to compare skill profiler'),
    '#default_value' => variable_get('iisp_skiller_compare_no'),
    '#description' => t("Enter the number of profiles that can compared by IISP skiller(numeric value)"),
    '#required' => TRUE,
	'#element_validate' => array('element_validate_number'),
  );
  
  $form['iisp_manager_compare_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of profilers to compare skill profiler'),
    '#default_value' => variable_get('iisp_manager_compare_no'),
    '#description' => t("Enter the number of profiles that can be compared by the IISP manager(numeric value)"),
	'#element_validate' => array('element_validate_number'),
    '#required' => TRUE,
  );


  return system_settings_form($form);
	
}