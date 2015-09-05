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
// Start single page profiler edit and delte
function profiler_info_list_form($form, $form_state) {
    if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
        return profiler_info_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['deletable_ids']));
    }
    
    $form['admin'] = profiler_info_admin_enquiries();
    return $form;
}


function profiler_info_multiple_delete_confirm($form, &$form_state, $deletable_ids) {
  
  global $base_url;
  global $user;
  $flag_set_delete = 0;
  $form['deletable_ids'] = array('#prefix' => '<ul>', '#suffix' => '</ul>', '#tree' => TRUE);
      foreach ($deletable_ids as $cid => $value) {
        $profiler_info_name = db_query('SELECT name FROM {iisp_profiles} WHERE id = :id', array(':id' => $cid))->fetchField();

        $form['deletable_ids'][$cid] = array(
          '#type' => 'hidden',
          '#value' => $cid,
          '#prefix' => '<li>',
          '#suffix' => check_plain($profiler_info_name) . "</li>\n",
        );
      }


  $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');

  $form['#submit'][] = 'profiler_info_multiple_delete_confirm_submit';

  $confirm_question = format_plural(count($deletable_ids),
      'Are you sure you want to delete this profile?',
      'Are you sure you want to delete these profiles?');
  return confirm_form($form,
                    $confirm_question,
                    'iisp_profiler/profiles/', t('This action cannot be undone.'),
                    t('Delete'), t('Cancel'));

}

function profiler_info_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {    
    profiler_info_delete_multiple(array_keys($form_state['values']['deletable_ids']));
    $count = count($form_state['values']['deletable_ids']);
    watchdog('profiler_info', 'Deleted @count profiler_info.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted 1 profiler info.', 'Deleted @count profiler info.'));
  }
  $form_state['redirect'] = 'iisp_profiler/profiles';
}

function profiler_info_delete_multiple($values){
  foreach($values as $val){
    $query = db_delete('iisp_profiles');
    $query->condition('id', $val)->execute();

  }
}


function profiler_info_admin_enquiries() {
  
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
    $operations = profiler_info_operations();
  
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
        '#validate' => array('profiler_info_form_list_validate'),
        '#submit' => array('profiler_info_form_list_submit'),
    );


    $header = array(
        'name' => array('data' => t('Name'), 'field' => 'fs.name', 'sort' => 'DESC'),
        'description' => array('data' => t('Description')),      
        'created' => array('data' => t('Date Created')),      
        'changed' => array('data' => t('Date Changed')),      
        'operations' => array('data' => t('Operations')),
    );

    //Start get the listing for iisp profiles
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
    //End get the listing for iisp profiles

    $destination = drupal_get_destination();
    $options = array();

    foreach ($result as $row)
    { 
        $options[$row->id] = array(
            'name' => l($row->name,'iisp_profiler/profiles/skill/'.$row->id),
            'description' => $row->description,
            'created' =>  format_date($row->created,'short'),
            'changed' => format_date($row->changed,'short'),
            'operations' => array('data' =>array(
                array(
                    '#prefix' => '<ul class="links inline" style="list-style:none">',
                    ),
                array(
                    '#prefix' => '<li>',
                    '#suffix' => '</li>',
                    '#type' => 'link',
                    '#title' => t('Edit'),
                    '#href' => "iisp_profiler/profiles/$row->id/edit",
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

function profiler_info_form_list_validate($form, &$form_state) {
  // Error if there are no items to select.
  if (!is_array($form_state['values']['deletable_ids']) || !count(array_filter($form_state['values']['deletable_ids']))) {
    form_set_error('', t('No profiler info selected.'));
  }
}

function profiler_info_form_list_submit($form, &$form_state) {
  $operations = profiler_info_operations();
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

function profiler_info_operations() {
  $operations = array(
    'delete' => array(
      'label' => t('Delete selected profiles'),
      'callback' => NULL,
    ),
  );
  return $operations;
}

function profile_form_page_edit($profile_id){
  $query = db_select('iisp_profiles', 'fs')
            ->fields('fs')
      ->condition('fs.id', $profile_id)
            ->execute()
            ->fetchObject();
   drupal_set_title(t('<em> Edit profile of  @title </em>', array('@title' => $query->name)), PASS_THROUGH);

   return drupal_get_form('profiler_info_form', $query);
}
// End single page profiler edit and delte

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
              ->condition('fs.uid',$user->uid)
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
    $profile_id = $profiler_info->id;
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
        $profile_id = 0;
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
if(!$profile_id){
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Select type'),
    '#options' => $type_array,
    '#default_value' =>$type,
    '#weight' => $weight++,
    '#required' => true,
  ); 
}

if(!$profile_id){
    $form['links'] = array(
      '#type' => 'textfield',
      '#title' => t('Share link'),
      '#weight' => $weight++,
      '#states' => array(
        'visible' => array(
          ':input[name="type"]' => array('value' => 'link'),
        ),
        'required' => array(
          ':input[name="type"]' => array('value' => 'link'),
        ),
      ),
      '#default_value' => $links,
    );
}

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

function profiler_info_form_validate($form, &$form_state){
  $sharing_links = $form_state['values']['links'];
  $type = $form_state['values']['type'];
  $profile_id = $form_state['values']['id'];
  if($type == 'link' && empty($sharing_links)){
      form_set_error('sharing_links','Share link is required');
  }
  if(!$profile_id){
    $query = db_select('iisp_profiles', 'n');
          $query->fields('n');
          $query->condition('n.sharing_links', $sharing_links);
    $profile_data = $query
            ->execute()
            ->fetchObject();
    if(!$profile_data){
        form_set_error('sharing_links','Import sharing link doesnt exist');
    }
  }
 return $form;
}

function profiler_info_form_submit($form, &$form_state){
  global $user;
  $result_profile_data = 0;
  $profiler_info = (object) $form_state['values'];
  $profiler_info->uid = $user->uid;
  $profiler_info->changed = REQUEST_TIME;

  if(empty($profiler_info->id)){
    $profiler_info->created = REQUEST_TIME;
    drupal_write_record('iisp_profiles', $profiler_info);
    if($profiler_info->type == 'link'){
          $query = db_select('iisp_profile_data', 'n');
          $query->fields('n');
          $query->leftJoin('iisp_profiles', 'o', '(n.iisp_profiles_id = o.id)');
          $query->condition('o.sharing_links', $profiler_info->links);
          $result_profile_data = $query
            ->execute()
            ->fetchAll();
    }
    if($result_profile_data){
      foreach($result_profile_data as $upd){
         $result =  db_insert('iisp_profile_data') 
                              ->fields(array(
                                'uid' => $user->uid,
                                'score' => $upd->score,
                                'iisp_profiles_id' => $profiler_info->id,
                                'iisp_skills_id' => $upd->iisp_skills_id,
                              ))
                              ->execute();
      }
    }
    $form_state['redirect'] = 'iisp_profiler/profiles/skill/'.$profiler_info->id;
  } else {
    drupal_write_record('iisp_profiles', $profiler_info, 'id');
    $form_state['redirect'] = 'iisp_profiler/profiles';
    drupal_set_message('Profile edited sucessfully');
  }

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

function ajax_skills_profile_name(){
    global $user;
    $result = db_select('iisp_profiles', 'pd')
              ->fields('pd')
              ->condition('pd.id',$_GET['iisp_profiles_id'])
              ->execute()
              ->fetchObject();
    if($result){
    echo json_encode($result); }
    else {
      $msg['success'] = false;
      echo json_encode($msg);
    }
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

function ajax_compare_profile(){
  global $base_url;
  global $user;
  $path = drupal_get_path('module', 'iisp_profiler');
    drupal_add_js($base_url . '/' . $path . '/js/profiler_add.js', array('type' => 'file', 'scope' => 'footer', 'weight' => 2000));
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

     //Start get user profile info
    $user_profile_list = db_select('iisp_profiles', 'fs')
              ->fields('fs')
              ->execute()
              ->fetchAll();  
    //End get user profile info  
        
   return theme('compare_page', array('skill_categories'=>$user_skill_categories,'skills'=>$user_skills,'user_profile_list'=>$user_profile_list));
}


