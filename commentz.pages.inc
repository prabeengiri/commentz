<?php
/**
 * @files
 * Page callback
 */

/**
 * Prepares the commentz for delete.
 */
function commentz_delete($cid) {
  $comment = comment_load($cid);
  $form_state = array();
  $form_state['build_info']['args'] = array($comment);
  // Load this using form_load_include so it's cached properly and works in the
  // ajax callback.
  form_load_include($form_state, 'inc', 'comment', 'comment.admin');
  $form_build = drupal_get_form('comment_confirm_delete', $comment);
  $form_build['#attributes']['class'] = 'better-comments-confirm';
  $form = drupal_render($form_build);
  $commands[] = ajax_command_append('#comment-wrap-' . $cid, $form);
  return array('#type' => 'ajax', '#commands' => $commands);
}