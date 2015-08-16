<?php

/**
 *
 * Admin page field settings iisp profiler
 * 
 */
// Add all forms definitions

//module_load_include('inc', 'coatings', 'coatings.form');
//module_load_include('inc', 'coatings', 'coatings.constant');
//module_load_include('inc', 'item', 'item.constant');

//
// Fields settings Listing page, create and edit page
//
function iisp_skills_skills($tab = '') {
  $output = '';
  switch ($tab) {
    case 'create':
      $build['iisp_skills_skills_create'] = drupal_get_form('iisp_skills_skills_form');
	  
	  $output = drupal_render($build);
	  break;
    default:
	
     $output .= '<ul class="action-links"><li>'.l(t('Add iisp skills'), 'admin/iisp_skills/skills/create', array('html'=>true, 'attributes' => array('class' => array('btn', 'btn-sm', 'btn-success'))))."</li></ul>";
	 $build['iisp_skills_skills_list'] = drupal_get_form('iisp_skills_skills_list_form');
     $output .= drupal_render($build);
	  
  }
  return $output;

}

function iisp_skills_skills_list_form($form, $form_state) {
    if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
        return iisp_skills_skills_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['deletable_ids']));
    }
    
    $form['admin'] = iisp_skills_skills_admin_enquiries();
    return $form;
}

function iisp_skills_skills_multiple_delete_confirm($form, &$form_state, $deletable_ids) {
  
	global $base_url;
	global $user;
	$flag_set_delete = 0;
	$form['deletable_ids'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);
	    foreach ($deletable_ids as $cid => $value) {
	      $iisp_skills_skillsname = db_query('SELECT name FROM {iisp_skills} WHERE id = :id', array(':id' => $cid))->fetchField();

	      $form['deletable_ids'][$cid] = array(
	        '#type' => 'hidden',
	        '#value' => $cid,
	        '#prefix' => '<li>',
	        '#suffix' => check_plain($iisp_skills_skillsname) . "</li>\n",
	      );
	    }


	$form['operation'] = array('#type' => 'hidden', '#value' => 'delete');

	$form['#submit'][] = 'iisp_skills_skills_multiple_delete_confirm_submit';

	$confirm_question = format_plural(count($deletable_ids),
	    'Are you sure you want to delete this report setting?',
	    'Are you sure you want to delete these report settings?');
	return confirm_form($form,
	                  $confirm_question,
	                  'admin/iisp_skills/skills/', t('This action cannot be undone.'),
	                  t('Delete'), t('Cancel'));

}

function iisp_skills_skills_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {    
    iisp_skills_skills_delete_multiple(array_keys($form_state['values']['deletable_ids']));
    $count = count($form_state['values']['deletable_ids']);
    watchdog('iisp_skills_skills', 'Deleted @count iisp_skills_skills.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted 1 iisp skill.', 'Deleted @count iisp skill.'));
  }
  $form_state['redirect'] = 'admin/iisp_skills/skills';
}

function iisp_skills_skills_delete_multiple($values){
	foreach($values as $val){
		$query = db_delete('iisp_skills');
		$query->condition('id', $val)->execute();

	}
}


function iisp_skills_skills_admin_enquiries() {
	
	global $user;
	
    //Add the bulk operation for iisp skill
    // Build the 'Update options' form.
     $form['options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Update options'),
        '#attributes' => array('class' => array('container-inline')),
        '#access' => TRUE,
    );
	
    $options = array();
	$operations = iisp_skills_skills_operations();
	
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
        '#validate' => array('iisp_skills_skills_form_list_validate'),
        '#submit' => array('iisp_skills_skills_form_list_submit'),
    );


    $header = array(
        'title_en' => array('data' => t('Name'), 'field' => 'fs.name', 'sort' => 'DESC'),  
		'weight' => array('data' => t('Weight')),
		'range' => array('data' => t('Score range')),  
		'status' => array('data'=> t('Status')),
		'changed' => array('data'=> t('Changed')),  
        'operations' => array('data' => t('Operations')),
    );

    //Start get the listing for iisp skill
  	$query = db_select('iisp_skills','fs');
    $count_query = clone $query;
    $count_query->addExpression('COUNT(fs.id)');
    $query = $query->extend('PagerDefault')->extend('TableSort');
    $query
      ->fields('fs', array('id', 'name', 'weight', 'scorerange', 'status', 'changed'))
      ->limit(10)
      ->orderBy('fs.weight','ASC')
      ->setCountQuery($count_query);
    $result = $query->execute();
    //End get the listing for iisp skill

    $destination = drupal_get_destination();
    $options = array();

    foreach ($result as $row)
    { 
			
			
        $options[$row->id] = array(
            'title_en' => $row->name,
            'weight' => $row->weight,
			'range' => $row->scorerange,
			'status' => $row->status == 1 ? "Published" : "Unpublished",
			'changed' => format_date($row->changed, 'short'), 
            'operations' => array('data' =>array(
                array(
                    '#prefix' => '<ul class="links inline">',),
                array(
                    '#prefix' => '<li>',
                    '#suffix' => '</li>',
                    '#type' => 'link',
                    '#title' => t('Edit'),
                    '#href' => "admin/iisp_skills/skills/$row->id/edit",
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
            '#empty' => t('No iisp skills are available.'),  
            '#attributes' => array (
                'id' => 'iisp_skills_table',
            )
        );

    $form['pager']['#markup'] = theme('pager');

    return $form;
}


/**
 * Implements hook_iisp_skills_skills_operations().
 */
function iisp_skills_skills_operations() {
  $operations = array(
    'delete' => array(
      'label' => t('Delete selected iisp skills'),
      'callback' => NULL,
    ),
  );
  return $operations;
}

/**
 * Validate iisp_skills_skills_form_list form submissions.
 *
 * Check if any iisp fields settings have been selected to perform the chosen
 * 'Update option' on.
 */
function iisp_skills_skills_form_list_validate($form, &$form_state) {
  // Error if there are no items to select.
  if (!is_array($form_state['values']['deletable_ids']) || !count(array_filter($form_state['values']['deletable_ids']))) {
    form_set_error('', t('No iisp skills categories selected.'));
  }
}


/**
 * Process iisp_skills_skills_form_list_submit form submissions.
 *
 * Execute the chosen 'Update option' on the selected trends.
 */
function iisp_skills_skills_form_list_submit($form, &$form_state) {
  $operations = iisp_skills_skills_operations();
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

function iisp_skills_skills_form($form, &$form_state, $iisp_skills_skills = NULL){
	$form = array();
	$form['#attributes']['class'][] = 'inform';
	
	$weight = 10;
	
	if(!empty($iisp_skills_skills)){
		$name = $iisp_skills_skills->name;
		$weight_field = $iisp_skills_skills->weight;
		$scorerange = $iisp_skills_skills->scorerange;
		
		$status       = $iisp_skills_skills->status;
		$field_desc   = $iisp_skills_skills->field_desc;
		$cat_id       = $iisp_skills_skills->iisp_skill_cat_id;
		
	    $form['id'] = array(
	    		'#type' => 'hidden',
	    		'#value' =>$iisp_skills_skills->id,
	  	  );	

	} else {
        $name          = "";
		$weight_field  = 10;
		$scorerange         = "";
		$status        = 1;
		$field_desc    = "";
		$cat_id        = "";
	}
	
	
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
	'#required' => true,
	'#weight' => $weight++,
	'#default_value' => $name,
  );
 	

  $form['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
	'#required' => true,
	'#weight' => $weight++,
	'#default_value' => $weight_field,
	'#element_validate' => array('element_validate_number'),
  );
  
  $form['scorerange'] = array(
    '#type' => 'textfield',
    '#title' => t('Score range'),
	'#description' => t('Please provide the score range in 0-6 format'),
	'#required' => true,
	'#weight' => $weight++,
	'#default_value' => $scorerange,
	
  );
  
  $form['status'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Status?'),
        '#options' => array('1' => 'Uncheck if you want to unpublish'),
        '#weight' => $weight++,
        '#default_value' => array('1' => $status),
    );
	
  $form['field_desc'] = array(
        '#type' => 'textarea',
        '#title' => t('Skill Description'),
		'#description' => t('Please enter the skill description here.'),
        '#weight' => $weight++,
		'#required' => true,
        '#default_value' => $field_desc,
    );	
	
	$form['iisp_skill_cat_id'] = array(
        '#type' => 'select',
        '#title' => t('Select skill category'),
        '#options' => get_dropdownlist('iisp_skill_cat', 'a', '', '', 'id', 'name'),
        '#weight' => $weight++,
		'#required' => true,
        '#default_value' => $cat_id,
    );
  
  
  

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save IISP skill'),
      '#weight' => $weight++,
	  '#prefix' => '<div class="form-item form-actions">',
	  '#suffix' => '</div>',
      '#submit' => array('iisp_skills_skills_form_submit'),
  );
  
  return $form;
	
}

function iisp_skills_skills_form_submit($form, &$form_state){
	global $user;
	$iisp_skills_skills = (object) $form_state['values'];
	$iisp_skills_skills->status = $form_state['values']['status'][1];
	$iisp_skills_skills->changed = REQUEST_TIME;
	
	if(empty($iisp_skills_skills->id)){
		$iisp_skills_skills->created = REQUEST_TIME;
		drupal_write_record('iisp_skills', $iisp_skills_skills);
	} else {
		drupal_write_record('iisp_skills', $iisp_skills_skills, 'id');
	}

	drupal_set_message('IISP skill category saved');
	$form_state['redirect'] = 'admin/iisp_skills/skills';
}

function iisp_skills_skills_page_edit($iisp_skills_skills_id){
	$query = db_select('iisp_skills', 'fs')
            ->fields('fs')
			->condition('fs.id', $iisp_skills_skills_id)
            ->execute()
            ->fetchObject();
   drupal_set_title(t('<em> Edit iisp skill  @title </em>', array('@title' => $query->name)), PASS_THROUGH);

   return drupal_get_form('iisp_skills_skills_form', $query);
}


