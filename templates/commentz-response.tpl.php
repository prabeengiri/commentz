<div class='commentz-response'>
  <?php foreach($commentz_responses as $response) :?>
    <div class='commentz-response-inner'>
      <?php print $response->text?>
      <span><?php print $response->author?></span>
      <span><?php print $respnose->created?></span>
    </div>
  <?php endforeach;?>
  <div class='commentz-response-form'><?php print t('Add A Comment');?></div>
</div>


