<?php

/**
 *
 * Profiler info
 * 
 */
//
// Sfia skill profilers page
//
function iisp_profiler($tab = '') {
 $output = '';
  $build['profiler_info_create'] = drupal_get_form('profiler_info_form');
  
  $output = drupal_render($build);
  return $output;
}

function iisp_profiler_skill_add($tab = '') {
  global $base_url;
  global $user;
  $path = drupal_get_path('module', 'iisp_profiler');
  drupal_add_js($base_url . '/' . $path . '/js/profiler_add.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2000));
    drupal_add_css($base_url . '/' . $path . '/css/custom-style.css', array('type' => 'external', 'weight' => '500'));


    //Start get user profile info
    $user_profile_info = db_select('iisp_profiles', 'fs')
              ->fields('fs')
              ->condition('fs.uid',$user->uid)
              ->execute()
              ->fetchObject();  
    //End get user profile info

    //Start get skill categorys         
    $user_skill_categories = db_select('iisp_skill_cat', 'sc')
              ->fields('sc')
              ->execute()
              ->fetchAll();  
    //End get skill categorys 

    //Start get skill types         
    $user_skills = db_select('iisp_skills', 'sk')
              ->fields('sk')
              ->execute()
              ->fetchAll();  
    //End get skill types          
 return theme('profiler_page', array('user_profile_info' => $user_profile_info,'skill_categories'=>$user_skill_categories,'skills'=>$user_skills));
}

function profiler_info_form($form, &$form_state, $profiler_info = NULL){
  $form = array();
  $form['#attributes']['class'][] = 'inform';
  
  $weight = 0;
  $type_array = array(
          ''=>'-Select-',
          'new'=>'New',
          'link'=>'Import from share link',
        );
  if(!empty($profiler_info)){
    $name = $profiler_info->name;
    $type = $profiler_info->type;
    $description = $profiler_info->description;
    $notes = $profiler_info->notes;
    $links = $profiler_info->links;
      $form['id'] = array(
          '#type' => 'hidden',
          '#value' =>$profiler_info->id,
        );  

  } else {
        $name    =  "";
        $type    =  array();
        $description  =  "";
        $notes =  "";   
        $links =  "";   
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

    $form['links'] = array(
      '#type' => 'textfield',
      '#title' => t('Share link'),
      '#weight' => $weight++,
      '#states' => array(
        'visible' => array(
          ':input[name="type"]' => array('value' => 'link'),
        ),
      ),
      '#default_value' => $links,
    );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#weight' => $weight++,
    '#required' => true,
    '#default_value' =>$description,
    '#description' => t('Description for Profiles'),      
  );

  $form['notes'] = array(
    '#type' => 'textarea',
    '#title' => t('Notes'),
    '#weight' => $weight++,
    '#required' => true,
    '#default_value' =>$notes,
    '#description' => t('Note for profiles'),      
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save profiler info'),
      '#weight' => $weight++,
      '#prefix' => '<div class="form-item form-actions">',
      '#suffix' => '</div>',
      '#ajax' => array(
        'callback' => 'profiler_info_form_submit',
        'wrapper' => 'profiler_info_form',
        'method' => 'replace',
        'effect' => 'fade',
      ),
  );
  
  return $form;
  
}


function profiler_info_form_submit($form, &$form_state){
  global $user;
  $profiler_info = (object) $form_state['values'];
  $profiler_info->uid = $user->uid;
  $profiler_info->created = REQUEST_TIME;
    $profiler_info->changed = REQUEST_TIME;
    drupal_write_record('iisp_profiles', $profiler_info);

  $form_state['redirect'] = 'iisp_profiler/profiles';
}


