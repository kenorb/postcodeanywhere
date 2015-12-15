<?php

/**
 * @file
 * Include file to handle the PCA callbacks.
 */

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_autocomplete($string = "") {
  // Make a string lowercase and remove all spaces.
  $string = str_replace(' ', '', strtolower($string));
  try {
    foreach (postcodeanywhere_findbypostcode($string, TRUE) as $row) {
      $data[$row['Id']] = $row['Place'] ?: $value['StreetAddress'];
    }
    if (count($data) > 2) {
      $data['number-results'] = t('%result found, keep typing to refine', array('%result' => format_plural(count($data), t('1 result'), '@count ' . t('results.'))));
    }
    $data['no-match'] = t("I can't see my address");
  }
  catch (Exception $e) {
    // Check logs for further details.
    $data = array('no-match' => t("I can't see the address."));
  }
  drupal_json_output($data);
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
function postcodeanywhere_findbypostcode($postcode = POSTCODEANYWHERE_PC_TEST, $returnArray = FALSE) {
  require_once drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_FindByPostcode.class.inc";
  $key = variable_get('postcodeanywhere_licence', POSTCODEANYWHERE_DEMO_KEY);
  $cid = str_replace(' ', '', "pca_pc_" . $postcode);

  if (!($data = _pca_get_cache($cid))) {
    try {
      $pca = new PostcodeAnywhere_Interactive_FindByPostcode($key, $postcode, "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        _pca_set_cache($cid, $data);
      }
    }
    catch (Exception $e) {
      watchdog_exception('postcodeanywhere', $e);
    }
  }
  return $returnArray ? (array) $data : drupal_json_output($data ?: array());
}

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_findbypartialpostcode($PartialPostcode = "WR2", $returnArray = FALSE) {
  require_once drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_FindByPartialPostcode.class.inc";
  $key = variable_get('postcodeanywhere_licence', POSTCODEANYWHERE_DEMO_KEY);
  $cid = str_replace(' ', '', "pca_pc_" . $PartialPostcode);

  if (!($data = _pca_get_cache($cid))) {
    try {
      $pca = new PostcodeAnywhere_Interactive_FindByPartialPostcode($key, $PartialPostcode, "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        _pca_set_cache($cid, $data);
      }
    }
    catch (Exception $e) {
      watchdog_exception('postcodeanywhere', $e);
    }
  }
  return $returnArray ? $data : drupal_json_output($data ?: array());
}

/**
 * AJAX callback to returns the full address details based on the Id.
 */
function postcodeanywhere_retrievebyid($id) {
  require_once drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_RetrieveById.class.inc";
  $key = variable_get('postcodeanywhere_licence', POSTCODEANYWHERE_DEMO_KEY);
  $cid = str_replace(' ', '', "pca_id_" . $id);

  if (!($data = _pca_get_cache($cid))) {
    try {
      $pca = new PostcodeAnywhere_Interactive_RetrieveById($key, $id, "English", "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        _pca_set_cache($cid, $data);
      }
    }
    catch (Exception $e) {
      watchdog_exception('postcodeanywhere', $e);
    }
  }
  drupal_json_output($data ?: array());
}

/**
 * Helper function to get results from cache.
 */
function _pca_get_cache($cid) {
  $format = variable_get('postcodeanywhere_format', POSTCODEANYWHERE_FORMAT);
  if ($cache = cache_get($cid, POSTCODEANYWHERE_CACHE)) {
    // Serialization of SimpleXMLElement is not alloweḑ, so doing some workaround.
    $data = $format == 'xmla.ws' || $format == 'xmle.ws' ? json_decode($cache->data, TRUE) : $cache->data;
  }
  if (!empty($data)) {
    drupal_add_http_header('X-Cached-By', 'Drupal PCA');
    return $data;
  }
  else {
    return FALSE;
  }
}

/**
 * Helper function to cache the results.
 */
function _pca_set_cache($cid, $data) {
  $format = variable_get('postcodeanywhere_format', POSTCODEANYWHERE_FORMAT);
  // Serialization of SimpleXMLElement is not alloweḑ, so doing some workaround.
  return cache_set($cid, $format == 'xmla.ws' || $format == 'xmle.ws' ? json_encode($data) : $data, POSTCODEANYWHERE_CACHE);
}
