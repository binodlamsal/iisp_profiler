<div id="content" class="col-md-12 ">                          
  <div class="title-accent">
    <h3>Profiler  &raquo;  <?php  echo ucwords($user_profile_info->name); ?></h3>
    <p>To enter your skills: click on any of the SFIA skills to view the skill description. Select your skill level by clicking on the appropriate number – you can remind yourself of the generic skills and levels of responsibility by selecting the `SFIA` button or clicking on the ‘i’ information button when viewing a skill description. Profiles are automatically saved and will appear in your list of profiles each time you access the system.</p>
 	<div class="col-md-9"><p>test</p><div>
  </div>

<!--  width: 20px;
    height: 20px;
    margin: 0px 6px;
    padding: 8px 12px;
    border-radius: 135px;
    background-color: #ccc;
    z-index: 10000 !important; -->
     
	<div class="panel-group" id="accordions-">
		<div class="panel panel-default">
		    <div class="panel-heading">
		      <h4 class="panel-title">
		        <a data-toggle="collapse" class="collapsed" data-parent="#accordions-" href="#accordion-1">
		          Vestibulum ante ipsum primis in faucibus orci?
		        </a>
		      </h4>
		    </div>
		    <div id="accordion-1" class="panel-collapse collapse" style="height: 0px;">
		      <div class="panel-body">
		        
		<!-- Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam laoreet sodales lacinia. Curabitur ut purus tincidunt, iaculis elit a, eleifend augue. Phasellus blandit augue vel sollicitudin blandit. -->

				<div class="panel-group" id="accordions-sub">
					<div class="panel panel-default">
					    <div class="panel-heading">
					      <h4 class="panel-title">
					        <a data-toggle="collapse" class="collapsed" data-parent="#accordions-sub" href="#accordion-11">
					          IT Governance

					          <!-- <input type="radio" name="test1">
					          <input type="radio" name="test2">
					          <input type="radio" name="test3">
					          <input type="radio" name="test4">
					          <input type="radio" name="test5">
					          <input type="radio" name="test6">
					          <input type="radio" name="test7"> -->
					      <span class="checkbox-wrapper">
					      <?php for($i=1; $i<=7; $i++) : ?>
					      <span class="checkbox-style"><?php echo $i; ?></span>
					  	  <?php endfor; ?>
					      </span>
					        </a>

					      </h4>
					    </div>
					    <div id="accordion-11" class="panel-collapse collapse" style="height: 0px;">
					      <div class="panel-body">
					        
					Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam laoreet sodales lacinia. Curabitur ut purus tincidunt, iaculis elit a, eleifend augue. Phasellus blandit augue vel sollicitudin blandit.
					      </div>
					      <span class="level-text" style="text-align:center; margin-left:48%"> 
					      		<p>Levels Not Set </p>
					            <p>You haven't set a level for this skill yet, see level descriptions below.</p>
					      </span>
					      <span class="toggle-span" style="text-align:center; margin-left:46%"> View &raquo; </span>
					      <div class="inner-accordion"style="display:none">
					      	<span>
					      		<p>If you meet any of the competencies for a level you can consider yourself to be at that level.</p>
					      		<p><input type="button" value="Set Level" class="button-primary btn btn-default" id="setlevel"><p>
					      		<p><a href="" class="toggle-span">Close Tab</a>
					      	</span>
					      </div>
					    </div>
					 </div>
					</div>
				</div>

		      </div>
		    </div>
		 </div>
	</div>
	<div class="col-md-3 left-panel-profile">
		<table> 
			<tr><td><input type="button" value="Share" class="button-primary btn btn-default" id="share-add-button"></td></tr>
			<tr><td><input type="button" value="Compare" class="button-primary btn btn-default" id="compare-add-button"></td></tr>
			<tr><td><input type="button" value="Print" class="button-primary btn btn-default" id="print-add-button"></td></tr>
			<tr><td><input type="button" value="SFIA" class="button-primary btn btn-default" id="sifa-add-button"></td></tr>
			<tr><td><input type="button" value="Skill" class="button-primary btn btn-default" id="skill-add-button"></td></tr>
		</table>
	</div>
</div>