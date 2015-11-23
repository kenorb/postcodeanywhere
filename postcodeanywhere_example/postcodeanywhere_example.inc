<?php

/**
 * @file
 */

/**
 * Menu callback used by AJAX request.
 * Which simulates PCA service response.
 */
function postcodeanywhere_example_response() {
  $uri = parse_url(request_uri(), PHP_URL_PATH);
  $path = drupal_get_path('module', 'postcodeanywhere_example') . '/samples';
  $file = substr(str_replace('/', '-', $uri), 1);
  if (strpos($file, 'xml')) {
    drupal_add_http_header('Content-Type', 'text/xml; utf-8');
    $file .= '.xml';
  } else if (strpos($file, 'json')) {
    drupal_add_http_header('Content-Type', 'application/json; utf-8');
    $file .= '.json';
  }
  if (file_exists($path . '/' . $file)) {
    print file_get_contents($path . '/' . $file);
    exit;
  } else {
    drupal_not_found();
  }
}
