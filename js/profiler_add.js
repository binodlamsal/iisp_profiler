jQuery(document).ready(function($) {
    var root = document.location.hostname;
    var pathArray = window.location.pathname.split('/');
    var secondLevelLocation = pathArray[1];
    var base_url = 'http://' + root;
    $('.share_div').hide();
    $('.toggle-span').click(function() {
        $(".inner-accordion").slideToggle("slow", function() {});
    });
    $('body').on('click', '.share_info', function() {
        var radio_share_val_yes = $('#share_info_yes_id').val();
        var radio_share_val_no = $('#share_info_no_id').val();
        if ($("#share_info_yes_id").is(":checked")) {
            $('.share_div').show();
        } else {
            $('.share_div').hide();
        }
    });
    var profile_info_id = $("#profile_info_id").val();
    $.ajax({
        url: base_url + '/' + secondLevelLocation + '/iisp_skills/ajax_skills_category_total',
        data: {
            "iisp_profiles_id": profile_info_id
        },
        dataType: 'json',
        method: 'POST',
        success: function(data) {
            $.each(data, function(key, val) {
                var score = val.tot_score;
                var cat_id = val.skill_cat_id;
                $('#skill_catid_total_' + cat_id).text(score);
            });
        },
        error: function() {
            //error loading content
        },
        complete: function() {
            // $('.score-not-set').css('background-color','green');
        }
    });
    $.ajax({
        url: base_url + '/' + secondLevelLocation + '/iisp_skills/ajax_skills_profile_data/' + profile_info_id,
        data: {
            "test": "test"
        },
        dataType: 'json',
        method: 'POST',
        success: function(data) {
            $.each(data, function(key, val) {
                var score = val.score;
                var skillLevel = val.iisp_skills_id;
                $('#setLevelDiv' + skillLevel + ' .level-set').text('Level ' + score);
                $('#setlevel-btn-value' + skillLevel).text('Level ' + score);
                $('#setlevel-btn-value' + skillLevel).attr("data-checkboxid", score);
                $('#checkbox-' + score + '-skill-' + skillLevel).css("background-color", "green");
                $('#checkbox-' + score + '-skill-' + skillLevel).css("border", "1px dotted #000");
                $('#checkbox-reset-skill-' + skillLevel).removeClass("score-not-set");
                $('#checkbox-reset-skill-' + skillLevel).addClass("score-already-set");
            });
        },
        error: function() {
            //error loading content
        },
        complete: function() {
            $('.score-not-set').css('background-color', 'green');
        }
    });
    $('#viewing_profile_id').change(function() {
        //alert(base_url); 
        window.location.replace(base_url + "/iisp_profiler/profiles/skill/" + $('#viewing_profile_id').val());
    });
});