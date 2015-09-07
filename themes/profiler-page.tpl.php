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
                <a data-toggle="collapse" data-parent="#accordion1" href="#collapseTwo<?php echo $sc->id;?>" class="collapsed">
                  <?php echo $sc->name; ?> 
                  <span class="total_skills" id="skill_catid_total_<?php echo $sc->id; ?>" style="float:right;"></span>
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
                      <h4 class="panel-title"><a data-title="<?php echo $sk->name ?>" data-toggle="collapse"  data-parent="#accordion2" href="#collapseInner<?php echo $sk->id;?>" class='collapsed'>
                       <?php echo drupal_substr($sk->name,0,45); ?>
                       <?php $scorerange = explode('-', $sk->scorerange);?>
                      </a>
                      <span class="checkbox-wrapper" style="    position: absolute;
                            left: 52%;
                            margin-top: -35px;">
                      <span class="checkbox-style collapsed  checkbox-reset clickable score-not-set checkbox-skill-<?php echo $sk->id; ?>" href="#collapseInner<?php echo $sk->id;?>" id="checkbox-reset-skill-<?php echo $sk->id; ?>" style="cursor:pointer;" onClick="resetLabels(<?php echo $sk->id; ?>)" value="<?php echo $sk->id; ?>">-</span>
                      <?php for($i=1; $i<=6; $i++) : ?>
                      <?php if ($i >= $scorerange[0] && $i <= $scorerange[1]) { ?>
                          <span class="checkbox-style collapsed clickable checkbox-skill-<?php echo $sk->id; ?>" id="checkbox-<?php echo $i; ?>-skill-<?php echo $sk->id; ?>" href="#collapseInner<?php echo $sk->id;?>" style="cursor:pointer;" onClick="setLabels(<?php echo $i; ?>, <?php echo $sk->id; ?>)" value="<?php  echo $i; ?>"><?php echo $i; ?></span>
                      <?php } else { ?>
                          <span class="checkbox-style" id="checkbox-<?php echo $i; ?>-skill-<?php echo $sk->id; ?>" style="border: 1px dotted #000;background-color:#A7A385" value=""><?php echo $i; ?></span>
                      <?php } ?>
                      <?php endfor; ?>
                      <!-- jQuery(this).parent().parent().children('a').removeClass('collapsed') -->
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
  <div class="col-md-3 left-panel-profile">
    <table> 
      <tr><td style='border-top:none;'><input type="button" value="Share" onClick="insertShareLink(<?php echo $user_profile_info->id; ?>,0)" class="button-primary btn btn-default profile-left-button" id="share-add-button"></td></tr>
      <tr><td style='border-top:none;'><input type="button" value="Compare" onclick="window.location.href='<?php echo $base_url; ?>/iisp_skills/compare/<?php echo $user_profile_info->id; ?>'" class="button-primary btn btn-default profile-left-button" id="compare-add-button"></td></tr>
      <tr><td style='border-top:none;'><input type="button" value="Print" class="button-primary btn btn-default profile-left-button" id="print-add-button"></td></tr>
      <tr><td style='border-top:none;'><input type="button" value="SFIA" class="button-primary btn btn-default profile-left-button" id="sifa-add-button"></td></tr>
      <tr><td style='border-top:none;'><input type="button" value="Skill" class="button-primary btn btn-default profile-left-button" id="skill-add-button"></td></tr>
    </table>
  </div>
</div>

<!-- Modal -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
  <div class="modal-dialog modal-lg" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title" id="myModalLabel">Share <?php  echo ucwords($user_profile_info->name); ?> </h4>
      </div>
      <div class="modal-body">
        <p> Do you want to share this profile with others?</p>
        <p>
          <input type="radio" name="radio_share" value="1" id= "share_info_yes_id" class="share_info">Yes
          <input type="radio" name="radio_share" value="0" id= "share_info_no_id" class="share_info" checked="checked">No
        </p>
        <div class="share_div">
          <p>
            It’s easy to share your skills profile using the 'Share' option. This creates a unique web link for your personal profile. You can share the link with colleagues, your employer or recruiters via email, LinkedIn or other social media. Click refresh to create a new link and disable previously shared versions of this profile. 
          </p>
          <p class="link-to-share"></p>
          <p class="share_link">
             <a href="http://localhost/infoseskills.net/?q=iisp_profiler/profiles/preview" class="btn btn-default" target="_blank">Preview</a>
             <a href="" class="btn btn-default email-sharelink" target="_blank">Email</a>
             <button type="button" class="btn btn-default ref-sharelink" onClick="insertShareLink(<?php echo $user_profile_info->id; ?>,1)">Refresh</button>
          </p>
        </div>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>
<script type="text/javascript">

function setLabels(label, skillLevel){
  debugger;
    var attrtoggle = jQuery('.checkbox-skill-'+skillLevel).attr('data-toggle');
    var attrparent = jQuery('.checkbox-skill-'+skillLevel).attr('data-parent');
  
  if(typeof attrtoggle == typeof undefined && typeof attrparent == typeof undefined){
    jQuery('.checkbox-skill-'+skillLevel).removeAttr('data-toggle','collapse');
    jQuery('.checkbox-skill-'+skillLevel).removeAttr('data-parent','#accordion2');
    jQuery('#checkbox-'+label+'-skill-'+skillLevel).attr('data-toggle','collapse');
    jQuery('#checkbox-'+label+'-skill-'+skillLevel).attr('data-parent','#accordion2');
  }
   // jQuery(this).parent().parent().children('a').removeClass('collapsed');
   jQuery('#setLevelDiv'+skillLevel + ' .level-set').text('Level ' + label); 
   jQuery('#setlevel-btn-value'+skillLevel).text('Set Level ' + label);
   jQuery('#setlevel-btn-value'+skillLevel).attr("data-checkboxid",label);
} 

function resetLabels(skillLevel){
    var resetattrtoggle = jQuery('.checkbox-skill-'+skillLevel).attr('data-toggle');
    var resetattrparent = jQuery('.checkbox-skill-'+skillLevel).attr('data-parent');
  if(typeof resetattrtoggle == typeof undefined && typeof resetattrparent == typeof undefined){
   debugger;
    jQuery('.checkbox-skill-'+skillLevel).removeAttr('data-toggle','collapse');
    jQuery('.checkbox-skill-'+skillLevel).removeAttr('data-parent','#accordion2');
    jQuery('#checkbox-reset-skill-'+skillLevel).attr('data-toggle','collapse');
    jQuery('#checkbox-reset-skill-'+skillLevel).attr('data-parent','#accordion2');
  }
   jQuery('#setlevel-btn-value'+skillLevel).text('Reset Level');
   jQuery('#setlevel-btn-value'+skillLevel).attr("data-checkboxid",0);
}

function insertShareLink(profileid,refresh_link){
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

function insertLabels(skillLevel,profileid,userid){
    var score = jQuery('#setlevel-btn-value'+skillLevel).attr('data-checkboxid');
    if(score != 0){ 
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
    }else{
     jQuery('.checkbox-skill'+skillLevel).css("background-color", "#CCC");
     jQuery('#checkbox-reset-skill-'+skillLevel).css("background-color", "green");
      jQuery.ajax({
                  url:'<?php echo $base_url; ?>/iisp_skills/remove_skills_profile',
                  data: {"iisp_skills_id":skillLevel,"iisp_profiles_id":profileid,"uid":userid},
                  dataType: 'json',
                  method:'POST',
                    success:function (data)
                    {

                    },
                });
    }
}
</script>