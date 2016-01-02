<?php
/**
 * @file Admin settings for sanitizer.
 */

/**
 * Settings admin configs.
 */
function sanitizer_settings() {
  return system_settings_form(array(
    '#prefix' => t('Sanitizing is done via the @sanitize command via @drush.', array(
      '@sanitize' => '<code>drush sanitize</code>',
      '@drush' => l('http://www.drush.org', 'Drush'),
    )),
    'sanitizer_profile_fields' => array(
      '#type' => 'textarea',
      '#title' => 'Profile fields',
      '#description' => t('Fields on user profiles which should be sanitized.'),
    ),
    'sanitizer_skip_users' => array(
      '#type' => 'textarea',
      '#title' => 'Users to skip',
      '#description' => t('You probably want to at least leave your own account alone.'),
    ),
    'sanitizer_email_domain' => array(
      '#type' => 'textfield',
      '#title' => 'Email domain',
      '#description' => t('Account email addresses will be changed to this domain.'),
    ),
    'sanitizer_password' => array(
      '#type' => 'textfield',
      '#title' => 'Password',
      '#description' => t('Password to give all users.'),
    ),
  ));
}
