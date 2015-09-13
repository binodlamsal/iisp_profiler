<?php global $user;
$skill_compare_no = 6;
if(array_key_exists('4', $user->roles)){
  $skill_compare_no = variable_get('iisp_skiller_compare_no');
}elseif(array_key_exists('2', $user->roles)){
  $skill_compare_no = variable_get('iisp_manager_compare_no');
}
?>
<?php global $base_url;?>
<div class="col-md-12 profile-compare">

  <div class="row">
    <div class="panel-body">
      <div class="col-md-6">
          <h2>Category and Skills</h2>
      </div>
      <?php for($i=1;$i<=$skill_compare_no;$i++) : ?>
        <div class="col-md-1">
            <button class="btn-default btn btn-small user-add-class" data-toggle="modal" data-target="#myModal" data-profile-pos-id="<?php echo $i; ?>"  id="profile-pos-id-<?php echo $i; ?>">ADD</button>
        </div>
      <?php endfor; ?>
    </div> 
  </div>
  <?php foreach($skill_categories as $sc): ?>
    <?php $skill = get_skills_by_skill_category($sc->id); ?>

  <div class="panel-group" id="accordion1">
    <div class="panel panel-default">
        <div class="panel-heading">
          <h4 class="panel-title">
            <a data-toggle="collapse" data-parent="#accordion1" href="#collapseTwo<?php echo $sc->id;?>" class='collapsed'>
              <span class='row'>
              <span class="col-md-6"><?php echo $sc->name; ?></span>
 
               <?php for($i=1;$i<=$skill_compare_no;$i++) : ?>
              <!-- <span class="col-md-1 compare-score compare-tot-score-<?php echo $sc->id; ?> comp-pos-<?php echo $i; ?>-skillcat-<?php echo $sc->id; ?>" id="skill-total-catid-<?php echo $sc->id; ?>-pos-<?php echo $i; ?>" style='text-align:center'> -->
              <span class="col-md-1 compare-score compare-pos-<?php echo $i;?> compare-tot-score-<?php echo $sc->id; ?> comp-pos-<?php echo $i; ?>-skillcat-<?php echo $sc->id; ?>" id="skill-total-catid-<?php echo $sc->id; ?>-pos-<?php echo $i; ?>">
                <span class="new-compare-pos-<?php echo $i;?>" id="new-skill-total-catid-<?php echo $sc->id; ?>-pos-<?php echo $i; ?>">0</span>
              </span>
              <?php endfor; ?>
            </a>
          </h4>
        </div>
        <div id="collapseTwo<?php echo $sc->id;?>" class="panel-collapse collapse">
          <?php if($skill) : ?>
          <?php foreach($skill as $sk) : ?>
            <div class="panel-body">
              <div class="row">
                  <div class="col-md-6">
                      <h4><?php echo $sk->name; ?></h4>
                  </div>
                  <?php for($i=1;$i<=$skill_compare_no;$i++) : ?>
                  <div class="col-md-1" style='text-align:center;'>
                      <span class='checkbox-style checkbox-pos-<?php echo $i; ?>' id="checkbox-skill-<?php echo $sk->id; ?>-pos-<?php echo $i; ?>">-</span>
                  </div>
                  <?php endfor; ?>
              </div> 
            </div>
          <?php endforeach; ?>
          <?php endif; ?>
        </div>
    </div>
  </div>
  <?php endforeach; ?>
</div>

<!-- Start modal for adding profiles -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title" id="myModalLabel">Add Profile </h4>
      </div>
      <div class="modal-body">
        <div class="form-group form-type-select">
            <select name="add_profile" class="form-select form-control" id="add_profile_id">
              <?php foreach($user_profile_list as $upl) : ?>
                <option value="<?php echo $upl->id; ?>" ><?php echo $upl->name; ?></option>
              <?php endforeach; ?>
            </select>
        </div>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-success btn-save-ap" >Save</button>
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>
<!-- End modal for adding profiles -->

<script type="text/javascript">
  function addProfiles(pos_id){
    jQuery.ajax({
                  url:'<?php echo $base_url; ?>/iisp_skills/ajax_set_share_link',
                  data: {"iisp_profiles_id":profileid,"refresh_link":refresh_link},
                  dataType: 'json',
                  method:'POST',
                    success:function (data)
                    {
                        jQuery('.link-to-share').text('Share link : ' + data.sharing_links);
                        jQuery('.email-sharelink').attr("href","mailto:?subject=Share&amp;body="+data.sharing_links);
                    },
                });
  }
</script>

<style type="text/css">
  html{
    overflow-x: auto;
  }

  .site-wrapper {
    overflow: visible;
    position: relative;
    width: 100%;
}

.container {
    width: 1190px;
    overflow-x: visible;
    white-space: nowrap;
}

.col-md-1 {
 width: 100px;
}

.col-md-6 {
 width: 553px;
}


</style>



    
  <?php 
     if(array_key_exists('4', $user->roles)){
        $get = variable_get('iisp_skiller_compare_no');
     }
     elseif(array_key_exists('2', $user->roles)){
        $get = variable_get('iisp_manager_compare_no');
     } else {
        $get = 6;

     }
     if($get < 6){
      $total  = "1190px";
     } else {
      $total  = (553 + (100*($get+2)));
     }     

     drupal_add_js('
        (function ($) {
            $(".container").css("width", "'.$total.'px");
        }(jQuery));', array('type' => 'inline', 'scope' => 'footer', 'weight' => 2000));
   ?>
