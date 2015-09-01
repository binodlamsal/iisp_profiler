<?php

function iisp_profiler_dashboard(){
global $user;
	
    $query = db_select('iisp_goals','fs');
	$query = $query->condition('fs.uid', $user->uid);
    $query
      ->fields('fs', array('id'))
      ->range(0, 3)
      ->orderBy('fs.id','DESC');
      $result = $query->execute()->fetchAll();


    $query = db_select('iisp_activities','fs');
	  $query = $query->condition('fs.uid', $user->uid);
    $query
      ->fields('fs', array('id'))
      ->range(0, 3)
      ->orderBy('fs.id','DESC');
      $result1 = $query->execute()->fetchAll();

	return theme('profiler_dashboard_page', array('goals_profiler' => $result, 'activities_profiler'=> $result1));	
}