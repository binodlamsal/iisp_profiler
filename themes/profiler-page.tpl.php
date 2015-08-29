<?php global $user; ?>
<?php global $base_url;?>

<div id="content" class="col-md-12 ">                          
  <div class="title-accent">
    <input type="hidden" value="<?php echo $user_profile_info->id; ?>" id="profile_info_id">
    <h3>Profiler  &raquo;  <?php  echo ucwords($user_profile_info->name); ?></h3>
    <p>To enter your skills: click on any of the SFIA skills to view the skill description. Select your skill level by clicking on the appropriate number – you can remind yourself of the generic skills and levels of responsibility by selecting the `SFIA` button or clicking on the ‘i’ information button when viewing a skill description. Profiles are automatically saved and will appear in your list of profiles each time you access the system.</p>
    <div class="col-md-9">
      <span class="profile-viewing">
        <p style="margin-left: 75%;">You are currently viewing</p>
        <div class="form-group form-type-select" style="width: 25%; margin-left: 75%;">
            <select name="view_profile" class="form-select form-control" id="viewing_profile_id">
              <?php foreach($user_profile_list as $upl) : ?>
                <option value="<?php echo $upl->id; ?>" <?php if($upl->id == $user_profile_info->id){ echo "selected";} else{echo "";} ?>><?php echo $upl->name; ?></option>
              <?php endforeach; ?>
            </select>
        </div>
      </span>
    <div>
  </div>
    <?php foreach($skill_categories as $sc): ?>
    <?php $skill = get_skills_by_skill_category($sc->id); ?>
       <div class="panel-group" id="accordion1">
          <div class="panel panel-default">
            <div class="panel-heading">
              <h4 class="panel-title">
                <a data-toggle="collapse" data-parent="#accordion1" href="#collapseTwo<?php echo $sc->id;?>">
                  <?php echo $sc->name; ?> 
                </a>
              </h4>
            </div>
            <div id="collapseTwo<?php echo $sc->id;?>" class="panel-collapse collapse">
              <div class="panel-body">

                <!-- Here we insert another nested accordion -->
                <?php if($skill) : ?>
                <?php foreach($skill as $sk) : ?>
                <div class="panel-group" id="accordion2">
                  <div class="panel panel-default">
                    <div class="panel-heading">
                      <h4 class="panel-title"><a data-toggle="collapse"  data-parent="#accordion2" href="#collapseInner<?php echo $sk->id;?>">
                       <?php echo $sk->name; ?>
                      </a>
                      <span class="checkbox-wrapper" style="    position: absolute;
                            left: 52%;
                            margin-top: -35px;">
                      <?php for($i=1; $i<=7; $i++) : ?>
                      <span class="checkbox-style checkbox-skill<?php echo $sk->id; ?>" id="checkbox-<?php echo $i; ?>-skill-<?php echo $sk->id; ?>" style="cursor:pointer;" onClick="setLabels(<?php echo $i; ?>, <?php echo $sk->id; ?>)" value="<?php  echo $i; ?>"><?php echo $i; ?></span>
                      <?php endfor; ?>
                      </span>         
                      </h4>
                    </div>
                    <!-- <div id="collapseInnerOne<?php //echo $sklil->id;?>" class="panel-collapse collapse in"> -->
                    <div id="collapseInner<?php echo $sk->id;?>" class="panel-collapse collapse">
                      <div class="panel-body">
                                  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam laoreet sodales lacinia. Curabitur ut purus tincidunt, iaculis elit a, eleifend augue. Phasellus blandit augue vel sollicitudin blandit.
                      </div>

                      <span class="level-text" id="setLevelDiv<?php echo $sk->id; ?>" style="text-align:center; margin-left:48%"> 
                          <p class="level-set">Levels Not Set </p>
                            <p class="level-set-desc">You haven't set a level for this skill yet, see level descriptions below.</p>
                      </span>
                      <span class="toggle-span" style="text-align:center; margin-left:46%"> View &raquo; </span>
                      <div class="inner-accordion" id="innerDiv<?php echo $sk->id; ?>">
                        <span>
                          <p class="competencies" style="margin-left: 11%;">If you meet any of the competencies for a level you can consider yourself to be at that level.</p>
                          <p class="setlevelbtn" style="margin-left: 42%"><button  onClick="insertLabels(<?php echo $sk->id; ?>,<?php echo $user_profile_info->id ?>, <?php echo $user->uid; ?>)" class="button-primary btn btn-default" id="setlevel-btn-value<?php echo $sk->id; ?>">Set Level</button><p>
                          <p data-toggle="collapse" class="collapsed" data-parent="#accordions-sub" style="margin-left:44%"><a href="#" class="toggle-span">Close Tab</a>
                        </span>
                      </div>
                    </div>
                  </div>
                </div>
                <?php endforeach; ?>
                <?php endif; ?>

                <!-- Inner accordion ends here -->

              </div>
            </div>
          </div>
        </div>
  <?php endforeach; ?>
  </div> 
  <div class="col-md-3 left-panel-profile">
    <table> 
      <tr><td><input type="button" value="Share" class="button-primary btn btn-default profile-left-button" id="share-add-button"></td></tr>
      <tr><td><input type="button" value="Compare" class="button-primary btn btn-default profile-left-button" id="compare-add-button"></td></tr>
      <tr><td><input type="button" value="Print" class="button-primary btn btn-default profile-left-button" id="print-add-button"></td></tr>
      <tr><td><input type="button" value="SFIA" class="button-primary btn btn-default profile-left-button" id="sifa-add-button"></td></tr>
      <tr><td><input type="button" value="Skill" class="button-primary btn btn-default profile-left-button" id="skill-add-button"></td></tr>
    </table>
  </div>
</div>
<script type="text/javascript">


function setLabels(label, skillLevel){
   jQuery('#setLevelDiv'+skillLevel + ' .level-set').text('Level ' + label); 
   jQuery('#setlevel-btn-value'+skillLevel).text('Set Level ' + label);
   jQuery('#setlevel-btn-value'+skillLevel).attr("data-checkboxid",label);
}

function insertLabels(skillLevel,profileid,userid){
    var score = jQuery('#setlevel-btn-value'+skillLevel).attr('data-checkboxid');
   jQuery('.checkbox-skill'+skillLevel).css("background-color", "#CCC");
   jQuery('#checkbox-'+score+'-skill-'+skillLevel).css("background-color", "green");
    jQuery.ajax({
                url:'<?php echo $base_url; ?>/iisp_skills/ajax_skills_profile',
                data: {"score":score,"iisp_skills_id":skillLevel,"iisp_profiles_id":profileid,"uid":userid},
                dataType: 'json',
                method:'POST',
                  success:function (data)
                  {

                  },
              });
}
</script>