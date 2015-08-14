<?php

/**
 *
 * Admin page field settings iisp profiler
 * 
 */
// Add all forms definitions

//
// Fields settings Listing page, create and edit page
//
function iisp_fields_settings($tab = '') {
  $output = '';
  switch ($tab) {
    case 'create':
      $build['iisp_fields_settings_create'] = drupal_get_form('iisp_fields_settings_form');
	  
	  $output = drupal_render($build);
	  break;
    default:
	
     $output .= '<ul class="action-links"><li>'.l(t('Add iisp field settings'), 'admin/iisp_skills/field_settings/create', array('html'=>true, 'attributes' => array('class' => array('btn', 'btn-sm', 'btn-success'))))."</li></ul>";
	 $build['iisp_fields_settings_list'] = drupal_get_form('iisp_fields_settings_list_form');
     $output .= drupal_render($build);
	  
  }
  return $output;

}

function iisp_fields_settings_list_form($form, $form_state) {
    if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
        return iisp_fields_settings_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['deletable_ids']));
    }
    
    $form['admin'] = iisp_fields_settings_admin_enquiries();
    return $form;
}

function iisp_fields_settings_multiple_delete_confirm($form, &$form_state, $deletable_ids) {
  
	global $base_url;
	global $user;
	$flag_set_delete = 0;
	$form['deletable_ids'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);
	    foreach ($deletable_ids as $cid => $value) {
	      $iisp_fields_settingsname = db_query('SELECT name FROM {iisp_field_settings} WHERE id = :id', array(':id' => $cid))->fetchField();

	      $form['deletable_ids'][$cid] = array(
	        '#type' => 'hidden',
	        '#value' => $cid,
	        '#prefix' => '<li>',
	        '#suffix' => check_plain($iisp_fields_settingsname) . "</li>\n",
	      );
	    }


	$form['operation'] = array('#type' => 'hidden', '#value' => 'delete');

	$form['#submit'][] = 'iisp_fields_settings_multiple_delete_confirm_submit';

	$confirm_question = format_plural(count($deletable_ids),
	    'Are you sure you want to delete this report setting?',
	    'Are you sure you want to delete these report settings?');
	return confirm_form($form,
	                  $confirm_question,
	                  'admin/iisp_skills/field_settings/', t('This action cannot be undone.'),
	                  t('Delete'), t('Cancel'));

}

function iisp_fields_settings_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {    
    iisp_fields_settings_delete_multiple(array_keys($form_state['values']['deletable_ids']));
    $count = count($form_state['values']['deletable_ids']);
    watchdog('iisp_fields_settings', 'Deleted @count iisp_fields_settings.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted 1 iisp field settings.', 'Deleted @count iisp field settings.'));
  }
  $form_state['redirect'] = 'admin/iisp_skills/field_settings';
}

function iisp_fields_settings_delete_multiple($values){
	foreach($values as $val){
		$query = db_delete('iisp_field_settings');
		$query->condition('id', $val)->execute();

	}
}


function iisp_fields_settings_admin_enquiries() {
	
	global $user;
	
    //Add the bulk operation for iisp field settings
    // Build the 'Update options' form.
     $form['options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Update options'),
        '#attributes' => array('class' => array('container-inline')),
        '#access' => TRUE,
    );
	
    $options = array();
	$operations = iisp_fields_settings_operations();
	
    foreach ($operations as $operation => $array) {
		
        $options[$operation] = $array['label'];
    }
   
    $form['options']['operation'] = array(
        '#type' => 'select',
        '#title' => t('Operation'),
        '#title_display' => 'invisible',
        '#options' => $options,
        '#default_value' => 'approve',
    );
    $form['options']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Update'),
        '#validate' => array('iisp_fields_settings_form_list_validate'),
        '#submit' => array('iisp_fields_settings_form_list_submit'),
    );


    $header = array(
        'title_en' => array('data' => t('Name'), 'field' => 'fs.name', 'sort' => 'DESC'),
		'default_advanced' => array('data' => t('Advanced field')),      
		'type' => array('data' => t('Type')),      
		'weight' => array('data' => t('Weight')),      
        'operations' => array('data' => t('Operations')),
    );

    //Start get the listing for iisp field settings
  	$query = db_select('iisp_field_settings','fs');
    $count_query = clone $query;
    $count_query->addExpression('COUNT(fs.id)');
    $query = $query->extend('PagerDefault')->extend('TableSort');
    $query
      ->fields('fs', array('id', 'name', 'default_advanced', 'type', 'weight'))
      ->limit(10)
      ->orderBy('fs.id','DESC')
      ->setCountQuery($count_query);
    $result = $query->execute();
    //End get the listing for iisp field settings

    $destination = drupal_get_destination();
    $options = array();

    foreach ($result as $row)
    { 
			
			
        $options[$row->id] = array(
            'title_en' => $row->name,
            'default_advanced' => get_active_variable($row->default_advanced),
            'type' => $row->type,
            'weight' => $row->weight,
            'operations' => array('data' =>array(
                array(
                    '#prefix' => '<ul class="links inline">',),
                array(
                    '#prefix' => '<li>',
                    '#suffix' => '</li>',
                    '#type' => 'link',
                    '#title' => t('Edit'),
                    '#href' => "admin/iisp_skills/field_settings/$row->id/edit",
                    '#attributes' => array('class' => array('edit', 'btn', 'btn-default', 'btn-sm', 'btn-icon', 'icon-left')),
                    '#options' => array('query' => $destination, 'html' => true)
					),
                array(
                    '#suffix' => '</ul>',),

            )),
        );
    }  
    
    $form['deletable_ids'] = array(
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $options,
            '#empty' => t('No iisp fields settings available.'),  
            '#attributes' => array (
                'id' => 'iisp_field_settings_table',
            )
        );

    $form['pager']['#markup'] = theme('pager');

    return $form;
}


/**
 * Implements hook_iisp_fields_settings_operations().
 */
function iisp_fields_settings_operations() {
  $operations = array(
    'delete' => array(
      'label' => t('Delete selected iisp fields settings'),
      'callback' => NULL,
    ),
  );
  return $operations;
}

/**
 * Validate iisp_fields_settings_form_list form submissions.
 *
 * Check if any iisp fields settings have been selected to perform the chosen
 * 'Update option' on.
 */
function iisp_fields_settings_form_list_validate($form, &$form_state) {
  // Error if there are no items to select.
  if (!is_array($form_state['values']['deletable_ids']) || !count(array_filter($form_state['values']['deletable_ids']))) {
    form_set_error('', t('No iisp fields settings selected.'));
  }
}


/**
 * Process iisp_fields_settings_form_list_submit form submissions.
 *
 * Execute the chosen 'Update option' on the selected trends.
 */
function iisp_fields_settings_form_list_submit($form, &$form_state) {
  $operations = iisp_fields_settings_operations();
  $operation = $operations[$form_state['values']['operation']];
  // Filter out unchecked trends
  $deletable_ids = array_filter($form_state['values']['deletable_ids']);
  if ($function = $operation['callback']) {
    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($deletable_ids), $operation['callback arguments']);
    }
    else {
      $args = array($deletable_ids);
    }
    call_user_func_array($function, $args);

    cache_clear_all();
  }
  else {
    // We need to rebuild the form to go to a second step. For example, to
    // show the confirmation form for the deletion of trends.
    $form_state['rebuild'] = TRUE;
  }
}

function iisp_fields_settings_form($form, &$form_state, $iisp_fields_settings = NULL){
	$form = array();
	$form['#attributes']['class'][] = 'inform';
	
	$weight = 0;
	$type_array = array(
					'textfield'=>'textfield',
					'select'=>'select',
					'checkbox'=>'checkbox',
					'range'=>'range',
					'date'=>'date'
				);
	if(!empty($iisp_fields_settings)){
		$name = $iisp_fields_settings->name;
		$type = $iisp_fields_settings->type;
		$default_advanced = $iisp_fields_settings->default_advanced;
		$weight_field = $iisp_fields_settings->weight;
	    $form['id'] = array(
	    		'#type' => 'hidden',
	    		'#value' =>$iisp_fields_settings->id,
	  	  );	

	} else {
        $name    =  "";
        $type    =  array();
        $default_advanced  =  0;
        $weight_field =  0;		
	}
	
	
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
	'#required' => true,
	'#weight' => $weight++,
	'#default_value' => $name,
  );

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Select type'),
  	'#options' => $type_array,
    '#default_value' =>$type,
  	'#weight' => $weight++,
  	'#required' => true,
  );

  $form['default_advanced'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Advanced?'),
  	'#options' => array('1'=>'Advanced field or not'),
  	'#weight' => $weight++,
    '#default_value' => array('1'=>$default_advanced),
  );
 	

  $form['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
	'#required' => true,
	'#weight' => $weight++,
	'#default_value' => $weight_field,
	'#element_validate' => array('element_validate_number'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save iisp fields settings'),
      '#weight' => $weight++,
	  '#prefix' => '<div class="form-item form-actions">',
	  '#suffix' => '</div>',
      '#submit' => array('iisp_fields_settings_form_submit'),
  );
  
  return $form;
	
}

function iisp_fields_settings_form_submit($form, &$form_state){
	global $user;
	$iisp_fields_settings = (object) $form_state['values'];
	$iisp_fields_settings->default_advanced = $iisp_fields_settings->default_advanced[1];
	if(empty($iisp_fields_settings->id)){
		drupal_write_record('iisp_field_settings', $iisp_fields_settings);
	} else {
		drupal_write_record('iisp_field_settings', $iisp_fields_settings, 'id');
	}

	drupal_set_message('IISP field setting saved');
	$form_state['redirect'] = 'admin/iisp_skills/field_settings';
}

function iisp_fields_settings_page_edit($iisp_fields_settings_id){
	$query = db_select('iisp_field_settings', 'fs')
            ->fields('fs')
			->condition('fs.id', $iisp_fields_settings_id)
            ->execute()
            ->fetchObject();
   drupal_set_title(t('<em> Edit iisp field settings  @title </em>', array('@title' => $query->name)), PASS_THROUGH);

   return drupal_get_form('iisp_fields_settings_form', $query);
}


