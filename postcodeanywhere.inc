<?php

/**
 * @file
 *   Include file to handle the PCA callbacks.
 */

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_findbypostcode($postcode = "WR2 6NJ") {
  require_once(drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_FindByPostcode.class.inc");
  $key = variable_get('postcodeanywhere_licence', '');

  $cid = "pca_pc_" . $id;
  $cache = cache_get($cid);
  $data = $cache->data;

  if ($data) {
    echo $data;
    drupal_json_output();
  } else {
    try {
      $pa = new PostcodeAnywhere_Interactive_FindByPostcode($key, $postcode, "");
      $pa->MakeRequest();
      if ($data = $pa->HasData()) {
        cache_set($cid, $data);
      }
    }
    catch (Exception $e) {
      $data['error'] = $e->getMessage();
    }
    drupal_json_output($data);
  }
}

/**
 * AJAX callback to returns the full address details based on the Id.
 */
function postcodeanywhere_retrievebyid($id) {
  require_once(drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_RetrieveById.class.inc");
  $key = variable_get('postcodeanywhere_licence', '');

  $cid = "pca_id_" . $id;
  $cache = cache_get($cid);
  $data = $cache->data;

  if ($data) {
    echo $data;
    drupal_json_output();
  }
  else {
    try {
      $pa = new PostcodeAnywhere_Interactive_RetrieveById($key, $id, "English", "");
      $pa->MakeRequest();
      if ($data = $pa->HasData()) {
        cache_set($cid, $data);
      }
    }
    catch (Exception $e) {
      $data['error'] = $e->getMessage();
    }
    drupal_json_output($data);
  }
}
