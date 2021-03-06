# include "fbcunit.bi"

SUITE( fbc_tests.functions.udt_result_call2 )

	const TEST_X_B = 123
	const TEST_X_S = 12345
	const TEST_X_I = 12345678
	const TEST_X_L = 12345678901234
	const TEST_X_F = 1234.5
	const TEST_X_D = 1234567890.1

	const TEST_Y_B = -123
	const TEST_Y_S = -12345
	const TEST_Y_I = -12345678
	const TEST_Y_L = -12345678901234
	const TEST_Y_F = -1234.5
	const TEST_Y_D = -1234567890.1

	type b_xy
		x as byte
		y as byte
	end type 

	type s_xy
		x as short
		y as short
	end type 

	type i_xy
		x as integer
		y as integer
	end type 

	type l_xy
		x as longint
		y as longint
	end type 

	type f_xy
		x as single
		y as single
	end type 

	type d_xy
		x as double
		y as double
	end type 

	#macro gen_retproc( tp )
		function ret_##tp ( ) as tp##_xy
			function = type( TEST_X_##tp, TEST_Y_##tp )
		end function 
	#endmacro

	gen_retproc( b )
	gen_retproc( s )
	gen_retproc( i )
	gen_retproc( l )
	gen_retproc( f )
	gen_retproc( d )

	#macro gen_passproc( tp )
		sub pass_##tp ( byval v as tp##_xy )
			CU_ASSERT_EQUAL( v.x, TEST_X_##tp )
			CU_ASSERT_EQUAL( v.y, TEST_Y_##tp )
		end sub
	#endmacro

	gen_passproc( b )
	gen_passproc( s )
	gen_passproc( i )
	gen_passproc( l )
	gen_passproc( f )
	gen_passproc( d )

	#macro do_test( tp )
		pass_##tp( ret_##tp( ) )
	#endmacro

	TEST( allTypes )
		do_test( b )
		do_test( s )
		do_test( i )
		do_test( l )
		do_test( f )
		do_test( d )
	END_TEST

END_SUITE
