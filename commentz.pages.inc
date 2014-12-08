<?php
/**
 * @files
 * Page callback
 */

/**
 * Prepares the commentz for delete.
 */
function commentz_delete_page($cid) {
  global $user;
  $commentz = commentz_load($cid);

  if (!user_access('delete commentz') || !(user_access('delete own commentz') && $user->uid == $commentz['uid'])) {
    return MENU_ACCESS_DENIED;
  }

  //$form_state = array();
  //$form_state['build_info']['args'] = array($commentz);
  // Load this using form_load_include so it's cached properly and works in the
  // ajax callback.
  //form_load_include($form_state, 'inc', 'comment', 'comment.admin');
  $form_build = drupal_get_form('commentz_confirm_delete_form', $commentz);
  //$form_build['#attributes']['class'] = 'better-comments-confirm';
  $form = render($form_build);
  $commands[] = ajax_command_append('#commentz-delete-confirm-' . $cid, $form);
  //$commands[] = ajax_command_invoke('#commentz-inner-' . $cid, 'addClass', array('commentz-gray'));

  // Hide Commentz Links.
  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-links ul.links" , 'addClass', array('hide'));
  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-links ul.links" , 'removeClass', array('show'));

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Menu callback for commentz response delete.
 */
function commentz_response_delete_page($response_id) {
  global $user;
  $response = commentz_load($response_id);

  if (!user_access('delete commentz') || !(user_access('delete own commentz') && $user->uid == $response['uid'])) {
    return MENU_ACCESS_DENIED;
  }

  commentz_response_delete($response_id);
  $commands[] = ajax_command_remove('#commentz-response-' . $response_id);
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Menu callback for the commentz edit
 */
function commentz_edit_page($cid) {

  $commentz = commentz_load($cid);

  global $user;
  if (!user_access('edit commentz') || !(user_access('edit own commentz') && $user->uid == $commentz['uid'])) {
    return MENU_ACCESS_DENIED;
  }

  $form_build = drupal_get_form('commentz_edit_form', $cid);

  $form = render($form_build);
  $commands[] = ajax_command_append('#commentz-inner-' . $cid . " .commentz-content-wrapper", $form);

  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-content", 'addClass', array('hide'));
  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-content", 'removeClass', array('show'));

  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-links", 'addClass', array('hide'));
  $commands[] = ajax_command_invoke('#commentz-inner-' . $cid . " .commentz-links", 'removeClass', array('show'));

  return array('#type' => 'ajax', '#commands' => $commands);
}