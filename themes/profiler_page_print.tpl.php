<?php global $user; ?>
<?php global $base_url;?>


<div class="col-md-12" id="printdiv">
  <!-- <a class='btn btn-default btn-small' href='<?php echo $base_url ?>/iisp_profiler/profiles/skill/<?php echo arg(2); ?>'>Back</a>
  <br/>
  <br/> -->
   <h2>Profiler  &raquo;  <?php  echo ucwords($user_profile_info->name); ?></h2>
      <span class="profile-viewing">
        <input type="hidden" value="<?php echo arg(2); ?>" id="profile_info_id">
        <!-- <p style="margin-left: 75%;">You are currently viewing</p>
        <div class="form-group form-type-select" style="width: 25%; margin-left: 75%;">
            <select name="view_profile" class="form-select form-control" id="viewing_profile_id">
              <?php foreach($user_profile_list as $upl) : ?>
                <option value="<?php echo $upl->id; ?>" <?php if($upl->id == $user_profile_info->id){ echo "selected";} else{echo "";} ?>><?php echo $upl->name; ?></option>
              <?php endforeach; ?>
            </select>
        </div> -->
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
            <div id="collapseTwo<?php echo $sc->id;?>" class="panel-collapse collapse in">
              <div class="panel-body">

                <!-- Here we insert another nested accordion -->
                <?php if($skill) : ?>
                <?php foreach($skill as $sk) : ?>
                <div class="panel-group" id="accordion2">
                  <div class="panel panel-default">
                    <div class="panel-heading">
                      <h4 class="panel-title"><a data-toggle="collapse"  data-parent="#accordion2" href="#collapseInner<?php echo $sk->id;?>" class='collapsed'>
                       <?php echo $sk->name; ?>
                       <?php $scorerange = explode('-', $sk->scorerange);?>
                      </a>
                      <span class="checkbox-wrapper" style="    position: absolute;
                            left: 52%;
                            margin-top: -35px;">
                      <span class="checkbox-style checkbox-reset score-not-set checkbox-skill<?php echo $sk->id; ?>" id="checkbox-reset-skill-<?php echo $sk->id; ?>" style="cursor:pointer;" onClick="resetLabels(<?php echo $sk->id; ?>)" value="<?php echo $sk->id; ?>">-</span>
                      <?php for($i=1; $i<=6; $i++) : ?>
                      <?php if ($i >= $scorerange[0] && $i <= $scorerange[1]) { ?>
                          <span class="checkbox-style checkbox-skill<?php echo $sk->id; ?>" id="checkbox-<?php echo $i; ?>-skill-<?php echo $sk->id; ?>" style="cursor:pointer;" onClick="setLabels(<?php echo $i; ?>, <?php echo $sk->id; ?>)" value="<?php  echo $i; ?>"><?php echo $i; ?></span>
                      <?php } else { ?>
                          <span class="checkbox-style" id="checkbox-<?php echo $i; ?>-skill-<?php echo $sk->id; ?>" style="background-color:#A7A385" value=""><?php echo $i; ?></span>
                      <?php } ?>
                      <?php endfor; ?>

                      <?php //for($i=1; $i<=7; $i++) : ?>
                      <!-- <span class="checkbox-style checkbox-skill<?php echo $sk->id; ?>" id="checkbox-<?php echo $i; ?>-skill-<?php echo $sk->id; ?>" style="cursor:pointer;" onClick="setLabels(<?php echo $i; ?>, <?php echo $sk->id; ?>)" value="<?php  echo $i; ?>"><?php echo $i; ?></span> -->
                      <?php //endfor; ?>
                      </span>         
                      </h4>
                    </div>
                    <!-- <div id="collapseInnerOne<?php //echo $sklil->id;?>" class="panel-collapse collapse in"> -->
                    <div id="collapseInner<?php echo $sk->id;?>" class="panel-collapse collapse">
                      <div class="panel-body">
                              <?php echo $sk->field_desc; ?>    
                      </div>

                      <span class="level-text" id="setLevelDiv<?php echo $sk->id; ?>" style="text-align:center; margin-left:48%"> 
                          <p class="level-set">Levels Not Set </p>
                            <p class="level-set-desc">You haven't set a level for this skill yet, see level descriptions below.</p>
                      </span>
                      <span class="toggle-span" style="text-align:center; margin-left:46%"> View &raquo; </span>
                      <div class="inner-accordion" id="innerDiv<?php echo $sk->id; ?>">
                        <span>
                          <p class="competencies" style="margin-left: 11%;">If you meet any of the competencies for a level you can consider yourself to be at that level.</p>
                          <p class="setlevelbtn" style="margin-left: 42%"><button  onClick="insertLabels(<?php echo $sk->id; ?>,<?php echo $user_profile_info->id ?>, <?php echo $user->uid; ?>)" class="button-primary btn btn-default levelbtn" id="setlevel-btn-value<?php echo $sk->id; ?>">Set Level</button><p>
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

<?php if(arg(3) != 'preview') { ?>
<script type="text/javascript">
   
  window.onload = function() { 

    setTimeout(function(){ 
    window.print(); 
    }, 3000);
  }
 <?php } ?>
</script>