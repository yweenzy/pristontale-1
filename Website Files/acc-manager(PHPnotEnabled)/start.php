<?php

function browser($user_agent){
	
    $browser  = $_SERVER['HTTP_USER_AGENT'];
    $browsers = array('ie'      => 'MSIE',
					  'chrome'  => 'Chrome',
					  'safari'  => 'Safari',
					  'opera'   => 'Opera',
					  'firefox' => 'Firefox');
    return (strpos($browser, $browsers[$user_agent]) !== false);
	
} 

if(browser('firefox') or browser('ie')){
	
        echo 'Using Mozilla Firefox is blocked for this system, please use another.';
		
		exit;

}

?>