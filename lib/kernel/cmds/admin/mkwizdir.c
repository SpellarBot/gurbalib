void main( string str ) {
  if( !str || str == "" ) {
    write( "Useage: mkwizdir <name>\n" );
    return;
  }
  if( SECURE_D->query_admin( this_player()->query_name() ) == 1 ) {
    SECURE_D->create_homedir( str );
  } else {
    write( "You need admin priveleges to make wizards.\n" );
  } 
}
