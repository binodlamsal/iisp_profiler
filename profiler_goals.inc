<?php

/**
 *
 * Admin page field settings iisp profiler activities
 * 
 */
// Add all forms definitions

//
// Fields settings Listing page, create and edit page
//
function iisp_profiler_activities($tab = '') {
  $output = '';
  switch ($tab) {
    case 'create':
      $build['iisp_profiler_activities_create'] = drupal_get_form('iisp_profiler_activities_form');
	  
	  $output = drupal_render($build);
	  break;
    default:
	
     $output .= '<ul class="action-links"><li style="list-style:none;">'.l('<i class="fa fa-plus"></i>&nbsp;'.t('Add Goal'), 'iisp_profiler/goals/create', array('html'=>true, 'attributes' => array('class' => array('btn', 'btn-sm', 'btn-success'))))."</li></ul>";
	 $build['iisp_profiler_activities_list'] = drupal_get_form('iisp_profiler_activities_list_form');
     $output .= drupal_render($build);
	  
  }
  return $output;

}

function iisp_profiler_activities_list_form($form, $form_state) {
    if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
        return iisp_profiler_activities_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['deletable_ids']));
    }else if(isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'pending'){
		return change_staus_of_activity($form_state['values']['deletable_ids'], 1);
	} else if(isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'inprogress'){
	    return change_staus_of_activity($form_state['values']['deletable_ids'], 2); 
	} else if(isset($form_state['values']['operation']) && $form_state['values']['operation']  == 'complete'){
	    return change_staus_of_activity($form_state['values']['deletable_ids'], 3);
	}
    
    $form['admin'] = iisp_profiler_activities_admin_enquiries();
    return $form;
}

function change_staus_of_activity($activities, $status){
	foreach($activities as $act){
		$num_updated = db_update('iisp_goals_data') // Table name no longer needs {}
		  ->fields(array(
			'value' => $status,
		  ))
		  ->condition('iisp_goals_id', $act, '=')
		  ->condition('iisp_field_settings_id', 6)
		  ->execute();
	}
	drupal_set_message('Changing status becomes successful');
	drupal_goto('iisp_profiler/goals');
}


function iisp_profiler_activities_multiple_delete_confirm($form, &$form_state, $deletable_ids) {
  
	global $base_url;
	global $user;
	$flag_set_delete = 0;
	$form['deletable_ids'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);
	    foreach ($deletable_ids as $cid => $value) {
	      $id = db_query('SELECT id FROM {iisp_goals} WHERE id = :id', array(':id' => $cid))->fetchField();

	      $form['deletable_ids'][$cid] = array(
	        '#type' => 'hidden',
	        '#value' => $cid,
	        '#prefix' => '<li>',
	        '#suffix' => 'goal '. check_plain($id) . "</li>\n",
	      );
	    }


	$form['operation'] = array('#type' => 'hidden', '#value' => 'delete');

	$form['#submit'][] = 'iisp_profiler_activities_multiple_delete_confirm_submit';

	$confirm_question = format_plural(count($deletable_ids),
	    'Are you sure you want to delete this report setting?',
	    'Are you sure you want to delete these report settings?');
	return confirm_form($form,
	                  $confirm_question,
	                  'iisp_profiler/goals/', t('This action cannot be undone.'),
	                  t('Delete'), t('Cancel'));

}

function iisp_profiler_activities_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {    
    iisp_profiler_activities_delete_multiple(array_keys($form_state['values']['deletable_ids']));
    $count = count($form_state['values']['deletable_ids']);
    watchdog('iisp goals', 'Deleted @count iisp goals.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted 1 goal.', 'Deleted @count goals.'));
  }
  $form_state['redirect'] = 'iisp_profiler/goals';
}

function iisp_profiler_activities_delete_multiple($values){
	foreach($values as $val){
		$query = db_delete('iisp_goals');
		$query->condition('id', $val)->execute();
		
		db_delete('iisp_goals_data')->condition('iisp_goals_id', $val)->execute();

	}
}


function iisp_profiler_activities_admin_enquiries() {
	global $base_url;
	$path = drupal_get_path('module', 'iisp_profiler');
	
	
	drupal_add_js($base_url . '/' . $path . '/js/stupidtable.js', array('type' => 'file', 'scope' => 'header', 'weight' => 0));
	
	drupal_add_js('(function ($) {
		$("table").stupidtable();
     }(jQuery));', 'inline', array('scope' => 'footer', 'weight' => 2800));
	
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
	$operations = iisp_profiler_activities_operations();
	
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
        '#validate' => array('iisp_profiler_activities_form_list_validate'),
        '#submit' => array('iisp_profiler_activities_form_list_submit'),
    );


    $header = array(
        'title_en' => array('data' => t('Title'), 'data-sort'=>'string', 'style'=>'cursor:pointer;'),  
		'status' => array('data' => t('Status'), 'data-sort'=>'string', 'style'=>'cursor:pointer;'),
		'start_date' => array('data' => t('Start Date'), 'data-sort'=>'date', 'style'=>'cursor:pointer;'),
		'end_date' => array('data' => t('End Date'), 'data-sort'=>'date', 'style'=>'cursor:pointer;'),   
		'reviewed' => array('data' => t('Reviewed'), 'data-sort'=>'date', 'style'=>'cursor:pointer;'),   
        'operations' => array('data' => t('Operations')),
    );

    //Start get the listing for iisp field settings
  	$query = db_select('iisp_goals','fs');
    $count_query = clone $query;
    $count_query->addExpression('COUNT(fs.id)');
    $query = $query->extend('PagerDefault')->extend('TableSort');
	$query = $query->condition('fs.uid', $user->uid);
    $query
      ->fields('fs', array('id'))
      ->limit(100)
      ->orderBy('fs.id','DESC')
      ->setCountQuery($count_query);
    $result = $query->execute();
    //End get the listing for iisp field settings

    $destination = drupal_get_destination();
    $options = array();
	

    foreach ($result as $row)
    { 
			
		$system_attribute_form_fields = db_select('iisp_goals_data', 'f')
	            ->fields('f')
	            ->condition('f.iisp_goals_id',$row->id)
	            ->condition('f.custom', '0');
	    $result = $system_attribute_form_fields->execute()->fetchALL();	
		$newarray = array();
		foreach($result as $res){
			$newarray[$res->iisp_field_settings_id] = $res;
		}
		
		if($newarray[6]->value == '1'){
			$status = "<span style='color:red'>Pending</span>";
		} else if($newarray[6]->value == '2'){
			$status = "<span style='color:#CCCC00'>In progress</span>";
		} else if($newarray[6]->value == '3'){
			$status = "<span style='color:green'>Complete</span>";
		}
		
		
		
			
        $options[$row->id] = array(
            'title_en' => l($newarray[3]->value, "iisp_profiler/goals/$row->id/edit", array('attributes' => array('style' => 'color:black;'))),
            'status' => $status,
			'start_date' => process_date($newarray[2]->value),
			'end_date' => process_date($newarray[1]->value),
			'reviewed' => process_date($newarray[8]->value),
            'operations' => array('data' =>array(
                array(
                    '#prefix' => '<ul class="links inline">',),
                array(
                    '#prefix' => '<li style="list-style:none;">',
                    '#suffix' => '</li>',
                    '#type' => 'link',
                    '#title' => t(' <i class="fa fa-pencil"></i> Edit'),
                    '#href' => "iisp_profiler/goals/$row->id/edit",
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
            '#empty' => t('No development goals are available.'),  
            '#attributes' => array (
                'id' => 'iisp_skill_cat_table',
            )
        );

    $form['pager']['#markup'] = theme('pager');

    return $form;
}


/**
 * Implements hook_iisp_skills_categories_operations().
 */
function iisp_profiler_activities_operations() {
  $operations = array(
    'delete' => array(
      'label' => t('Bulk delete iisp goals'),
      'callback' => NULL,
    ),
	'pending' => array(
      'label' => t('Mark selected as pending'),
      'callback' => NULL,
    ),
	'inprogress' => array(
      'label' => t('Mark selected as in progress'),
      'callback' => NULL,
    ),
	'complete' => array(
      'label' => t('Mark selected as complete'),
      'callback' => NULL,
    ),
  );
  return $operations;
}

/**
 * Validate iisp_skills_categories_form_list form submissions.
 *
 * Check if any iisp fields settings have been selected to perform the chosen
 * 'Update option' on.
 */
function iisp_profiler_activities_form_list_validate($form, &$form_state) {
  // Error if there are no items to select.
  if (!is_array($form_state['values']['deletable_ids']) || !count(array_filter($form_state['values']['deletable_ids']))) {
    form_set_error('', t('No iisp goals selected.'));
  }
}


/**
 * Process iisp_skills_categories_form_list_submit form submissions.
 *
 * Execute the chosen 'Update option' on the selected trends.
 */
function iisp_profiler_activities_form_list_submit($form, &$form_state) {
  $operations = iisp_profiler_activities_operations();
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

function iisp_profiler_activities_form($form, &$form_state, $activities = NULL){
	global $base_url;
	$path = drupal_get_path('module', 'iisp_profiler');
	drupal_add_js($base_url . '/' . $path . '/js/src/jquery.tagsinput.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2000));
	drupal_add_js($base_url . '/' . $path . '/js/src/tagsinput-callback.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2000));
	drupal_add_js($base_url . '/' . $path . '/js/src/addeditlinked.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2000));
	drupal_add_css($base_url . '/' . $path . '/js/src/jquery.tagsinput.css', array('type' => 'external', 'weight' => '500'));
	
	global $user;
	$form = array();
	$form['#attributes']['class'][] = 'inform';
	
	if(!empty($activities)){
		
		$form['id'] = array(
	    		'#type' => 'hidden',
	    		'#value' =>$activities->id,
	  	  );	
		
		$system_attribute_form_fields = db_select('iisp_goals_data', 'f')
	            ->fields('f')
	            ->condition('f.iisp_goals_id', $activities->id);
	    $result = $system_attribute_form_fields->execute()->fetchALL();	
		$newarray = array();
		foreach($result as $res){
			if($res->custom == '1'){
				$newarray[$res->iisp_field_settings_id.'-custom'] = $res;
		   } else {
		   	    $newarray[$res->iisp_field_settings_id] = $res;
		   }
		}
		
		
	} else {
		
		
	}
	
	
	$weight = 10;
	
 $system_attribute_form_fields = db_select('iisp_field_settings', 'fs')
	            ->fields('fs')
	            // ->condition('fs.uid',$user->uid)
				->orderBy('fs.weight', 'ASC');
 $result =  $system_attribute_form_fields ->execute()->fetchAll();
 
 
 $advanced_fields = db_select('iisp_field_user_data', 'ud')
	            ->fields('ud')
	            ->condition('ud.uid',$user->uid);
 
 $result_normal = array();
 
 foreach($result as $key => $fields){
	 $result_normal[$fields->id] = $fields;
 }		
 		
 
 $result_adv =  $advanced_fields->execute()->fetchAll();


 if(count($result_adv) == 0){
	
    $advanced_fields = db_select('iisp_field_settings', 'ud')
	            ->fields('ud', array(id));
    $advanced_fields->condition('ud.default_advanced', 1);
	$result_adv =  $advanced_fields ->execute()->fetchAll(); 
    
}

 $result_advance = array();
 
 foreach($result_adv as $rev){
	if (array_key_exists($rev->iisp_field_settings_id, $result_normal)) {
		
		$result_advance[$rev->iisp_field_settings_id] = $result_normal[$rev->iisp_field_settings_id];
		unset($result_normal[$rev->iisp_field_settings_id]);
	}

	if (array_key_exists($rev->id, $result_normal)) {
		
		$result_advance[$rev->id] = $result_normal[$rev->id];
		unset($result_normal[$rev->id]);
	}
 }
 
 
 	
	$form['field_info_first'] = array(
    '#prefix' => '<div class="row"><div class="col-md-8" style="background:#f7f7f7; padding:10px; border-radius:10px; border:1px solid #eaeaea;" ><legend><i class="fa fa-key"></i> &nbsp; Add/Edit Goals</legend><br/><br/><br/><p>* Are mandantory fields</p>',
	'#type' => 'markup',
	'#weight' => $weight++,	
	);			
				
foreach($result_normal as $fields)	{
	
	if($fields->type == 'date'){
		$fields->type = 'date_popup';
		$form['name_'.$fields->id] = array(
			'#type' => $fields->type,
			'#title' => $fields->name,
			'#description'=> $fields->description,
			'#weight' => $weight++,
			'#date_format' => 'Y-m-d',
			'#default_value' => $newarray[$fields->id]->value,
	   );
	}
	elseif($fields->name == 'Status'){
		
		$form['name_'.$fields->id] = array(
			'#type' => 'radios',
			'#title' => $fields->name,
			'#weight' => $weight++,
			'#description'=> $fields->description,
			'#options' => array('1' => 'Pending', '2' => 'In Progress', '3' => 'Complete'),
			'#default_value' => $newarray[$fields->id]->value,
		  );
		
	}else if($fields->type == 'range'){
		
	      $skill_types_fields = db_select('iisp_sifaplus_skill_types', 'fs')
	            ->fields('fs')
	            ->execute()
	            ->fetchAll();
	  $options_skill_types = get_keyvalue_array($skill_types_fields[0]->name);
	  
	  	$form['name_'.$fields->id] = array(
		    '#type' => 'select',
		    '#title' => t('Skill enhanced'),
		  	'#weight' => $weight++,
			'#options' => $options_skill_types,
			'#default_value' => $newarray[$fields->id]->value,
		    '#description'=> $fields->description,
			'#select2' => array(
			  'width' => '200',
			  'placeholder' => t('Select categories'),
			  'allowClear'   => TRUE,
			  'minimumResultsForSearch' => '1',
			),
		  );
	
	} else {
		
		if($fields->name == 'Title'){
			$required = true;	
		}else{
			$required = false;	
		}	
	$form['name_'.$fields->id] = array(
    '#type' => $fields->type,
    '#title' => $fields->name,
	'#required' => $required,
	'#description'=> $fields->description,
	'#weight' => $weight++,
	'#default_value' => $newarray[$fields->id]->value,
  );
  
	}
  
}

$normal_fields_custom = db_select('iisp_goals_custom_fields', 'ud')
	            ->fields('ud')
	            ->condition('ud.uid',$user->uid)->execute()->fetchAll();
				
foreach($normal_fields_custom as $fields){
	
 if($fields->advanced == '0') {

    if($fields->type == 'int' || $fields->type == 'decimal' ){

    		$type = 'textfield';
    		$validate = array('element_validate_number');

			$form['custom_'.$fields->id] = array(
		    '#type' => $type,
		    '#title' => $fields->title,
			'#weight' => $weight++,
			'#element_validate' => $validate,
			'#default_value' => $newarray[$fields->id.'-custom']->value,
		  );
    }
    else if($fields->type == 'date'){
    		$type = 'date_popup';
    		$validate = array();

			$form['custom_'.$fields->id] = array(
		    '#type' => $type,
		    '#title' => $fields->title,
			'#weight' => $weight++,
			'#date_format' => 'Y-m-d',
			'#element_validate' => $validate,
			'#default_value' => $newarray[$fields->id.'-custom']->value,
		  );

    } else {
    		$type  = "textfield";
    		$validate = array();

    			
			$form['custom_'.$fields->id] = array(
		    '#type' => $type,
		    '#title' => $fields->title,
			'#weight' => $weight++,
			'#element_validate' => $validate,
			'#default_value' => $newarray[$fields->id.'-custom']->value,
		  );
    }
  
 }
	
}			

 

$form['field_info'] = array(
  '#type' => 'markup',
   '#markup' => '<div class="panel-group" id="accordions-">
<div class="panel panel-default">
    <div class="panel-heading">
      <h4 class="panel-title">
        <a data-toggle="collapse" class="collapsed" data-parent="#accordions-" href="#accordion-1">
         <i class="fa fa-star"></i> &nbsp; Advanced fields
        </a>
      </h4>
    </div>
    <div id="accordion-1" class="panel-collapse collapse" style="height: auto;">
      <div class="panel-body">
        ',
	'#weight' => $weight++,	
);

foreach($result_advance as $fields)	{
	
	if($fields->type == 'date'){
		$fields->type = 'date_popup';
		$form['name_'.$fields->id] = array(
			'#type' => $fields->type,
			'#title' => $fields->name,
			'#description'=> $fields->description,
			'#weight' => $weight++,
			'#date_format' => 'Y-m-d',
			'#default_value' => $newarray[$fields->id]->value,
	   );
	}
	else if($fields->name == 'Status'){
		
		
		$form['name_'.$fields->id] = array(
			'#type' => 'radios',
			'#title' => $fields->name,
			'#weight' => $weight++,
			'#description'=> $fields->description,
			'#options' => array('1' => 'Pending', '2' => 'In Progress', '3' => 'Complete'),
			'#default_value' => $newarray[$fields->id]->value,
		  );
		
	} elseif($fields->type == 'range'){
		
		
	      $skill_types_fields = db_select('iisp_sifaplus_skill_types', 'fs')
	            ->fields('fs')
	            ->execute()
	            ->fetchAll();
	  $options_skill_types = get_keyvalue_array($skill_types_fields[0]->name);
	  
	  	$form['name_'.$fields->id] = array(
		    '#type' => 'select',
		    '#title' => t('Skill enhanced'),
		  	'#weight' => $weight++,
			'#options' => $options_skill_types,
			'#default_value' => $newarray[$fields->id]->value,
		    '#description'=> $fields->description,
			'#select2' => array(
			  'width' => '200',
			  'placeholder' => t('Select categories'),
			  'allowClear'   => TRUE,
			  'minimumResultsForSearch' => '1',
			),
		  );
	
	} else {
		
		if($fields->name == 'Title'){
			
			$required = true;
		}else{
			$required = false;	
		}	
	$form['name_'.$fields->id] = array(
    '#type' => $fields->type,
    '#title' => $fields->name,
	'#required' => $required,
	'#description'=> $fields->description,
	'#weight' => $weight++,
	'#default_value' => $newarray[$fields->id]->value,
  );
  
	}
  
}	

foreach($normal_fields_custom as $fields){
	
 if($fields->advanced == '1') {

    if($fields->type == 'int' || $fields->type == 'decimal' ){

    		$type = 'textfield';
    		$validate = array('element_validate_number');

			$form['custom_'.$fields->id] = array(
		    '#type' => $type,
		    '#title' => $fields->title,
			'#weight' => $weight++,
			'#element_validate' => $validate,
			'#default_value' => $newarray[$fields->id.'-custom']->value,
		  );
    }
    else if($fields->type == 'date'){
    		$type = 'date_popup';
    		$validate = array();

			$form['custom_'.$fields->id] = array(
		    '#type' => $type,
		    '#title' => $fields->title,
			'#weight' => $weight++,
			'#date_format' => 'Y-m-d',
			'#element_validate' => $validate,
			'#default_value' => $newarray[$fields->id.'-custom']->value,
		  );

    } else {
    		$type  = "textfield";
    		$validate = array();

    			
			$form['custom_'.$fields->id] = array(
		    '#type' => $type,
		    '#title' => $fields->title,
			'#weight' => $weight++,
			'#element_validate' => $validate,
			'#default_value' => $newarray[$fields->id.'-custom']->value,
		  );
    }
  
 }
	
}		
	
$form['field_info_end'] = array(
   '#type' => 'markup',
   '#markup' => '</div></div></div></div>',
   '#suffix' => '</div><div class="col-md-4">
    <hr class="visible-sm visible-xs lg"><h3>Activitiy linked to goal</h3>',
   '#weight' => $weight++,
);  

$system_attribute_form_fields = db_select('linked_data', 'ld')
	            ->fields('ld')
	            ->condition('ld.goalid', $activities->id)
				->orderBy('ld.id', 'ASC');
 $result =  $system_attribute_form_fields ->execute()->fetchAll();
 
 $newa = array();
 foreach($result as $rs){
 	$newa[$rs->activityid] = $rs->goalid;
 }

$resultact = get_all_activities_of_current_user();
 
$suffix = ''; 
foreach($resultact as $key=>$res){

 if(array_key_exists($key, $newa)){
 	
  
  $suffix .= '<div style="width:100%;background:#CCC;margin:5px; padding:5px;" class="btn btn-small btn-default" id="remove'.$key.'">'.l($res, 'iisp_profiler/activities/'.$key.'/edit').'<input type="hidden" name="activities[]" value="'.$key.'"><span style="margin-right:10px; float:right; clear:both;" onclick="removedom('.$key.')">X</span></div>';
}

}



$form['linked_activities']  = array(
  	 '#type' => 'select',
     '#title' => 'Activities Linked to Goal',
	 '#title_display'=>'invisible',
	 '#options' => get_all_activities_of_current_user(),
	 '#suffix' => '<div class="linklist">
	 	'.$suffix.'

	 </div></div></div>',
	 '#weight' => $weight++,
	 //'#default_value' => $activities->iisp_activities_id,
  );
 	

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save Goal'),
      '#weight' => $weight++,
	  '#prefix' => '<br/><div class="form-item form-actions">',
	  '#suffix' => '</div>',
      '#submit' => array('iisp_profiler_activities_form_submit'),
  );
  
  
  
  return $form;
	
}

function iisp_profiler_activities_form_submit($form, &$form_state){
	global $user;
	
	$form_data = (object) $form_state['values'];
	unset($form_data->submit);
	unset($form_data->form_build_id);
	unset($form_data->form_token);
	unset($form_data->form_id);
	unset($form_data->op);
	
	
	$goals = (object)array();
	$goals->changed = REQUEST_TIME;
	$goals->uid = $user->uid;
	$goals->iisp_activities_id = $form_data->linked_activities;
	
	if(empty($form_data->id)){
		$goals->created = REQUEST_TIME;
		drupal_write_record('iisp_goals', $goals);
	} else {
		$goals->id = $form_data->id;
		drupal_write_record('iisp_goals', $goals, 'id');
	}

	db_delete('linked_data')->condition('goalid', $goals->id)->execute();	
	
	foreach($_POST['activities'] as $act){

		$linked_data = (object)array();
		$linked_data->activityid = $act;
		$linked_data->goalid     = $goals->id;

		drupal_write_record('linked_data', $linked_data);
    }

	
	db_delete('iisp_goals_data')->condition('iisp_goals_id', $form_data->id)->execute();
	foreach($form_data as $key=>$val){
		$goals_data = (object)array();
		$goals_data->uid = $user->uid;
		
		$data = explode("_", $key);
		if($data[0] == 'custom'){
		  $goals_data->custom = 1; 
		}
		
		$goals_data->value = $val;
		$goals_data->iisp_goals_id = $goals->id;
		$goals_data->iisp_field_settings_id = $data[1];
		
		drupal_write_record('iisp_goals_data', $goals_data);
		
	}
	

	drupal_set_message('IISP goal saved');
	$form_state['redirect'] = 'iisp_profiler/goals';
}

function iisp_profiler_activities_page_edit($activity_id){
	$query = db_select('iisp_goals', 'fs')
            ->fields('fs')
			->condition('fs.id', $activity_id)
            ->execute()
            ->fetchObject();
   drupal_set_title(t('Edit goal'));

   return drupal_get_form('iisp_profiler_activities_form', $query);
}

function get_all_activities_of_current_user(){
    global $user;

	$query = db_select('iisp_activities', 'fs')
            ->fields('fs', array('id'));
	$query->leftJoin('iisp_activities_data', 'o', '(fs.id = o.iisp_activities_id)');
	$query->condition('o.iisp_field_settings_id', '3');
	$query->condition('fs.uid', $user->uid);
	$query->fields('o', array('value'));
    $result = $query->execute()->fetchAll();
	
	$returnRes = array();
	$returnRes[''] = 'Select';
	foreach($result as $res){
		$returnRes[$res->id] = $res->value;
	}
	
	return $returnRes;
			
			
}