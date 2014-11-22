<?php
/**
 * @file
 * There definition and preprocess
 */
/**
 * Implements hook_theme().
 */
function commentz_theme($existing, $type, $theme, $path) {
  return array(
    'commentz' => array(
      'template' => 'theme/commentz',
      'render element' => 'commentz'
    ),
    'commentz_wrapper' => array(
      'template' => 'theme/commentz-wrapper',
      'render element' => 'commentz_wrapper'
    ),
    'commentz_response' => array(
      'template' => 'theme/commentz-response',
      'render element' => 'commentz_response'
    ),
  );
}

/**
 * Implement preprocess comment wrapper.
 */
function commentz_preprocess_commentz_wrapper(&$variables, $hook) {
  $variables['count'] = $variables['commentz_wrapper']['commentzs']['#count'];
  $variables['commentzs'] = $variables['commentz_wrapper']['commentzs'];
  $variables['commentz_form'] = $variables['commentz_wrapper']['commentz_form'];
}

function commentz_preprocess_commentz(&$variables, $hook) {

  $comment = $variables['commentz']['#comment'];
  $interval = time() - $comment['created'];
  $variables['comment']['created'] = '' . format_interval($interval, 1) . t(' ago');
  unset($variables['elements']['#comment']);
  $variables['comment']['author'] = l($comment['name'], "user/" . $comment['uid']);
  $variables['comment']['avatar'] = commentz_get_avatar();
  $variables['comment']['comment_id'] = $comment['cid'];
  $variables['comment']['content'] = $comment['body'];
  $variables['comment']['links'] = $variables['commentz']['links'];

  $responses = isset($variables['commentz']['commentz_responses']) ? $variables['commentz']['commentz_responses'] : array();
  $variables['comment']['responses'] = $responses;

}

function commentz_preprocess_commentz_response(&$variables) {
  $response = $variables['commentz_response']['#response'];

  $interval = time() - $response['created'];
  $variables['created'] = '' . format_interval($interval, 1) . t(' ago');
  $variables['author'] = l($response['name'], 'user/' . $response['uid']);
  $variables['response'] = $response['body'];
  $variables['comment_id'] = $response['cid'];
}
