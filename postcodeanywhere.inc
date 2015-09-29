<?php

/**
 * @file
 *   Include file to handle the PCA callbacks.
 */

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_autocomplete($string = "") {
  $matches = array();

  if (strlen($string) >= 5) { // If postcode is 5 chars in length or more, it's full post code ...
    postcodeanywhere_findbypostcode($string);
  }
  else if (strlen($string) > 3) { // ... otherwise if it's 3-4 in length, it's partial.
    postcodeanywhere_findbypartialpostcode($string);
  } else {
    drupal_json_output($matches);
  }
}

/**
 * Form element validate handler for PCA autocomplete element.
 */
function postcodeanywhere_autocomplete_validate($element, &$form_state) {
  $values = $form_state['values'];

  // @todo? strlen($string) <= 3
  // form_error($form['node'], t('Sorry, the post code is too short.'));
}

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_findbypostcode($postcode = "LL11 5HJ") { // LL11 5HJ (or WR2 6NJ) is a test code.
  require_once(drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_FindByPostcode.class.inc");
  $key = variable_get('postcodeanywhere_licence', '');

  $cid = "pca_pc_" . $postcode;
  $cache = cache_get($cid);
  $data = $cache->data;

  if (empty($data)) {
    try {
      $pca = new PostcodeAnywhere_Interactive_FindByPostcode($key, $postcode, "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        cache_set($cid, $data);
      } else {
        $data = array();
      }
    }
    catch (Exception $e) {
      $data['error'] = $e->getMessage();
    }
  }
  drupal_json_output($data);
}

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_findbypartialpostcode($PartialPostcode = "WR2") {
  require_once(drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_FindByPartialPostcode.class.inc");
  $key = variable_get('postcodeanywhere_licence', '');

  $cid = "pca_pc_" . $PartialPostcode;
  $cache = cache_get($cid);
  $data = $cache->data;

  if (empty($data)) {
    try {
      $pca = new PostcodeAnywhere_Interactive_FindByPartialPostcode($key, $PartialPostcode, "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        cache_set($cid, $data);
      } else {
        $data = array();
      }
    }
    catch (Exception $e) {
      $data['error'] = $e->getMessage();
    }
  }
  drupal_json_output($data);
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

  if (empty($data)) {
    try {
      $pca = new PostcodeAnywhere_Interactive_RetrieveById($key, $id, "English", "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        cache_set($cid, $data);
      } else {
        $data = array();
      }
    }
    catch (Exception $e) {
      $data['error'] = $e->getMessage();
    }
  }
  drupal_json_output($data);
}

