<?php
/**
 * @file Drush command to sanitize your Drupal data.
 */

define('SANITIZE_DEFAULT_ENV', 'live');

/**
 * Implements hook_drush_help().
 */
function sanitizer_drush_help($section) {
  switch ($section) {
    case 'drush:sanitize':
      return dt('Sanitize the site of private information. See admin page for options.');
  }
}

/**
 * Implements hook_drush_command().
 */
function sanitizer_drush_command() {
  return array('sanitize' => array(
    'description' => 'Sanitize the site of private information.',
    'examples' => array(
      'drush sanitize' => 'Download and install the latest backup of live production.',
      'drush caboose test' => 'Download and install latest backup of test environment.',
      'drush caboose dev' => 'Download and install latest backup of dev environment.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_CONFIGURATION,
    'aliases' => array('sz'),
  ));
}

/**
 * Command callback.
 *
 * @param $env
 *   The dev/test/live environment to target.
 */
function drush_sanitize($env = DEFAULT_ENV) {
  // @todo Get configured fields on users and dummy vaules.
  // variable_get('sanitizer_profile_fields');
  $sanitize_fields = array(
    'profile_hidden_email' => 'abc@example.com',
    'profile_last_name'    => 'Smith',
    'profile_phone'        => '555-555-5555',
  );
  // Overwrite fields.
  drush_print("Overwriting profile fields.\n");
  foreach($sanitize_fields as $field => $value) {
    $query = "UPDATE field_data_field_$field SET field_{$field}_value = '$value'";
    shell_exec(_drush_sql_connect() . ' -e "' . $query . '"');
    // Legacy approach.
    //$result = drush_invoke_process($target_site, 'sql-query', array($query), $options, $backend_options);
  }

  // @todo Get dummy email domain.
  // variable_get('sanitizer_email_domain');
  $email_domain = '@example.com';
  // @todo Get configured skipped users.
  // variable_get('sanitizer_skip_users');
  $unaltered_accounts = array(
    'me@example.com',
    'you@example.com',
  );
  // @todo Get configured user one password.
  // variable_get('sanitizer_password');
  $password   = 'password';
  // Account details.
  drush_print("Overwriting account data.\n");
  // Leave some accounts alone.
  if (isset($unaltered_accounts)) {
    $accounts = array_map(function($value) {
      return '\'' . $value . '\'';
    }, $unaltered_accounts);
    $where = 'WHERE mail <> ' . implode(' AND mail <> ', $accounts);
  }
  $query = "UPDATE users SET mail = CONCAT(PASSWORD(mail), '$email_domain'), pass = '$password', init = CONCAT(PASSWORD(init), '$email_domain') $where";
  shell_exec(_drush_sql_connect() . ' -e "' . $query . '"');

  // Done.
  drush_print("Sanitized.\n");
}
