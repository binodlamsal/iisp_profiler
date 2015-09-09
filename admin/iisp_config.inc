<?php

function iisp_admin_config_form($form, $form_state){
  $form = array();

  $form['application_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of the application'),
    '#default_value' => variable_get('application_name'),
    '#description' => t("Please enter the name of the application example:name Profiler"),
    '#required' => TRUE,
  );
  
  $form['iisp_skiller_role_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the  skiller role id(numeric value)'),
    '#default_value' => variable_get('iisp_skiller_role_id'),
	'#element_validate' => array('element_validate_number'),
    '#description' => t("Please enter the skiller role id in number"),
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
    '#description' => t("Enter the number of profiles that can compared by skiller(numeric value)"),
    '#required' => TRUE,
	'#element_validate' => array('element_validate_number'),
  );
  
  $form['iisp_manager_compare_no'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of profilers to compare skill profiler'),
    '#default_value' => variable_get('iisp_manager_compare_no'),
    '#description' => t("Enter the number of profiles that can be compared by the  manager(numeric value)"),
	   '#element_validate' => array('element_validate_number'),
    '#required' => TRUE,
  );

  $help = variable_get('iisp_profiler_help');

  $form['iisp_profiler_help'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Profiler help page'),
    '#default_value' => $help['value'],
    '#description' => t("Enter the help page contents here."),
    //'#required' => TRUE,
  );


  $help = variable_get('iisp_profiler_skills');

  $form['iisp_profiler_skills'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Profiler skills page'),
    '#default_value' => $help['value'],
    '#description' => t("Enter skills page contents here."),
    //'#required' => TRUE,
  );

  $tour1 = variable_get('take_tour_1');

  $form['take_tour_1'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Enter tour slider first description'),
    '#default_value' => $tour1['value'],
    '#description' => t("Enter tour slider first description you can add images and text"),
    //'#required' => TRUE,
  );

  $tour2 = variable_get('take_tour_2');

  $form['take_tour_2'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',

    '#title' => t('Enter tour slider second description'),
    '#default_value' => $tour2['value'],
    '#description' => t("Enter tour slider second description you can add images and text"),
    //'#required' => TRUE,
  );

  $tour3 = variable_get('take_tour_3');

  $form['take_tour_3'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Enter tour slider third description'),
    '#default_value' => $tour3['value'],
    '#description' => t("Enter tour slider third description you can add images and text"),
    //'#required' => TRUE,
  );

  $tour4 = variable_get('take_tour_4');

  $form['take_tour_4'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Enter tour slider fourth description'),
    '#default_value' => $tour4['value'],
    '#description' => t("Enter tour slider fourth description you can add images and text"),
    //'#required' => TRUE,
  );

  $tour5 = variable_get('take_tour_5');

  $form['take_tour_5'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Enter tour slider fifth description'),
    '#default_value' => $tour5['value'],
    '#description' => t("Enter tour slider third description you can add images and text"),
    //'#required' => TRUE,
  );

  $tour1 = variable_get('take_tour_6');

  $form['take_tour_6'] = array(
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#title' => t('Enter tour slider sixth description'),
    '#default_value' => $tour6['value'],
    '#description' => t("Enter tour slider sixth description you can add images and text"),
    //'#required' => TRUE,
  );


  return system_settings_form($form);
	
}