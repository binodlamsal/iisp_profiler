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
  switch ($tab) {
    case 'create':
      $build['profiler_info_create'] = drupal_get_form('profiler_info_form');
    
    $output = drupal_render($build);
    break;
    default:
  
     $output .= '<h2> Profiles </h2><ul class="action-links" style="list-style:none;margin-left:-40px"><li>'.l(t('<i class="fa fa-plus"></i> &nbsp; Create Profile'), 'iisp_profiler/profiles/create', array('html'=>true, 'attributes' => array('class' => array('btn', 'btn-sm', 'btn-success'))))."</li></ul>";
   $build['profiler_info_list'] = drupal_get_form('profiler_info_list_form');
     $output .= drupal_render($build);
    
  }
  return $output;
}

function profiler_info_list_form($form, $form_state){
  global $user;
    $header = array(
        'name' => array('data' => t('Name'), 'field' => 'fs.name', 'sort' => 'DESC'),
        'description' => array('data' => t('Description')),      
        'created' => array('data' => t('Date Created')),      
        'changed' => array('data' => t('Date Changed')),      
    );

    //Start get the listing for iisp profile
    $query = db_select('iisp_profiles','fs');
    $count_query = clone $query;
    $count_query->addExpression('COUNT(fs.id)');
    $query = $query->extend('PagerDefault')->extend('TableSort');
    $query
      ->fields('fs', array('id', 'name', 'description', 'created', 'changed'))
      ->condition('fs.uid',$user->uid)
      ->limit(10)
      ->orderBy('fs.id','DESC')
      ->setCountQuery($count_query);
    $result = $query->execute();
    //End get the listing for iisp profile

    $destination = drupal_get_destination();
    $options = array();

    foreach ($result as $row)
    { 
        $options[$row->id] = array(
            'name' => l($row->name,'iisp_profiler/profiles/skill/'.$row->id),
            'description' => $row->description,
            'created' =>  format_date($row->created,'short'),
            'changed' => format_date($row->changed,'short'),
        );
    }  
    
    $form['gallerys'] = array(
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $options,
            '#empty' => t('No profiles available'),  
            '#attributes' => array (
                'id' => 'iisp_profile_table',
            )
        );

    // $form['pager']['#markup'] = theme('pager');

    return $form;
}

function iisp_profiler_skill_add($profile_id) {
  global $base_url;
  global $user;
  $path = drupal_get_path('module', 'iisp_profiler');
  drupal_add_js($base_url . '/' . $path . '/js/profiler_add.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2000));
    drupal_add_css($base_url . '/' . $path . '/css/custom-style.css', array('type' => 'external', 'weight' => '500'));


    //Start get user profile info by id
    $user_profile_info = db_select('iisp_profiles', 'fs')
              ->fields('fs')
              ->condition('fs.id',$profile_id)
              ->execute()
              ->fetchObject();  
    //End get user profile info by id

    //Start get user profile info
    $user_profile_list = db_select('iisp_profiles', 'fs')
              ->fields('fs')
              ->execute()
              ->fetchAll();  
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

    //Start get profiles skill levels that already exists
    $user_profile_data_info = db_select('iisp_profile_data', 'pd')
              ->fields('pd')
              ->condition('pd.iisp_profiles_id',$profile_id)
              ->execute()
              ->fetchAll();        
    //End get profiles skill levels that already exists      
 return theme('profiler_page', array('user_profile_info' => $user_profile_info,'skill_categories'=>$user_skill_categories,'skills'=>$user_skills,'user_profile_data_info'=>$user_profile_data_info,'user_profile_list'=>$user_profile_list));
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
      '#submit' => array('profiler_info_form_submit'),
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
    
    $form_state['redirect'] = 'iisp_profiler/profiles/skill/'.$profiler_info->id;
}

function ajax_skills_profile(){
  $check_user_set_profile = check_profile_skills($_GET['iisp_skills_id'],$_GET['iisp_profiles_id']);
  if($check_user_set_profile){
      $check_save = db_update('iisp_profile_data')
                          ->fields(array(
                            'score' => $_GET['score'],
                          ))
                          ->condition('iisp_profiles_id', $_GET['iisp_profiles_id'])
                          ->condition('iisp_skills_id',$_GET['iisp_skills_id'])
                          ->execute();
  }
  else{
    $data = (object) array(
        'uid'=>$_GET['uid'],
        'score'=>$_GET['score'],
        'iisp_profiles_id'=>$_GET['iisp_profiles_id'],
        'iisp_skills_id'=>$_GET['iisp_skills_id'],
    );
    $check_save = drupal_write_record('iisp_profile_data',$data);
  }
  
  if($check_save){
    $msg['success'] = true;
  }else{
    $msg['success'] = false;
  }
  echo json_encode($msg);
}

function ajax_share_link_profile(){
  global $base_url;
  // Check if previously inserted share link is present or not in case of refresh link = 0
  $user_profile_info = get_user_profile_info($_GET['iisp_profiles_id']);

  if(empty($user_profile_info->sharing_links) || $_GET['refresh_link'] == 1){
    $share_unique_id = md5(uniqid(mt_rand(), true));
    $share_link = $base_url.'/iisp_profiler/profiles/share/'.$share_unique_id;
    $check_save = db_update('iisp_profiles')
                        ->fields(array(
                          'sharing_links' => $share_link,
                        ))
                        ->condition('id', $_GET['iisp_profiles_id'])
                        ->execute();  
  }

  //Get the previously stored sharing link
  $user_new_profile_info = get_user_profile_info($_GET['iisp_profiles_id']);

  if($check_save){
    $msg['success'] = true;
    $msg['sharing_links'] = $user_new_profile_info->sharing_links;
  }else{
    $msg['success'] = false;
    $msg['sharing_links'] = $user_new_profile_info->sharing_links;
  }
  echo json_encode($msg);
}

function get_user_profile_info($profile_id){
    $result = db_select('iisp_profiles', 'pd')
              ->fields('pd')
              ->condition('pd.id',$profile_id)
              ->execute()
              ->fetchObject();

    return $result;
}

function ajax_skills_profile_data($profile_id){
  global $user;
    $user_profile_data_info = db_select('iisp_profile_data', 'pd')
              ->fields('pd')
              ->condition('pd.iisp_profiles_id',$profile_id)
              ->execute()
              ->fetchAll();
    if($user_profile_data_info){
    echo json_encode($user_profile_data_info); }
    else {
      $msg['success'] = false;
      echo json_encode($msg);
    }
}

function remove_skills_profile(){
  $check_user_set_profile = check_profile_skills($_GET['iisp_skills_id'],$_GET['iisp_profiles_id']);
  if($check_user_set_profile){
      $check_delete = db_delete('iisp_profile_data')
                          ->condition('iisp_profiles_id', $_GET['iisp_profiles_id'])
                          ->condition('iisp_skills_id',$_GET['iisp_skills_id'])
                          ->execute();
  }
  
  if($check_delete){
    $msg['success'] = true;
  }else{
    $msg['success'] = false;
  }
  echo json_encode($msg);
}


