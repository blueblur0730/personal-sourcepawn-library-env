#if defined _int64_included
	#endinput
#endif
#define _int64_included

/// x < y
stock bool UInt32LT(int x, int y) {
	/// why this works:
	/// 0x80000000 < 0 -> has to be false::
	/// (0x80000000^0x80000000) < (0^0x80000000)
	/// 0 < 0x80000000 -> true!
	return (x^0x80000000) < (y^0x80000000);
}

/// x > y
stock bool UInt32GT(int x, int y) {
	return UInt32LT(y, x);
}

/// x >= y
stock bool UInt32GE(int x, int y) {
	return !UInt32LT(x,y);
}

/// x <= y
stock bool UInt32LE(int x, int y) {
	return !UInt32GT(x,y);
}

stock int PopCount(int x) {
	int count = 0;
	for( int i = x; i > 0; count++ ) {
		i &= (i - 1);
	}
	return count;
}


enum {
	INT128_BIT_LEN    = 128,
	
	INT64_STR_LEN     = 32,
	INT64_BIT_LEN     = 64,
	
	INT32_BIT_LEN     = 32,
	INT32_BIT_LEN_IDX = 5,
	
	INT_MIN           = 0x80000000,
	INT_MAX           = 0x7FFFFFFF,
};
enum {
	INT64_LEN  = INT64_BIT_LEN / INT32_BIT_LEN,
	INT128_LEN = INT128_BIT_LEN / INT32_BIT_LEN,
};


stock int[] I64FromParts(int h, int l) {
	int output[INT64_LEN];
	output[1] = h; output[0] = l;
	return output;
}
stock int[] I64FromInt(int x) {
	int output[INT64_LEN];
	buf[0] = x;
	buf[1] = (x < 0)? -1 : 0;
	return output;
}

/// StringToInt64(const char[] str, int result[2], int nBase);

stock void PrintI64(int a[INT64_LEN]) {
	PrintToServer("int64::(%x_%x)", a[1], a[0]);
}

/// int I64ToString(const int num[2], char[] str, int maxlength);
stock int I64ToStr(int a[INT64_LEN], char buf[INT64_STR_LEN]) {
	if( a[1] ) {
		return Format(buf, sizeof(buf), "0x%x_%.8x", a[1],a[0]);
	}
	return Format(buf, sizeof(buf), "0x%x", a[0]);
}


/// I64 bitwise ops:
stock int PopCount64(int a[INT64_LEN]) {
	return PopCount(a[0]) + PopCount(a[1]);
}
stock int[] And64(int a[INT64_LEN], int b[INT64_LEN]) {
	int output[INT64_LEN];
	output[0] = a[0] & b[0]; output[1] = a[1] & b[1];
	return output;
}
stock int[] Or64(int a[INT64_LEN], int b[INT64_LEN]) {
	int output[INT64_LEN];
	output[0] = a[0] | b[0]; output[1] = a[1] | b[1];
	return output;
}
stock int[] Xor64(int a[INT64_LEN], int b[INT64_LEN]) {
	int output[INT64_LEN];
	output[0] = a[0] ^ b[0]; output[1] = a[1] ^ b[1];
	return output;
}
stock int[] Not64(int a[INT64_LEN]) {
	int output[INT64_LEN];
	output[0] = ~a[0]; output[1] = ~a[1];
	return output;
}

/// Shift Arithmetic Left
stock int[] SAL64(int a[INT64_LEN], int n) {
	if( n < 0 ) {
		return SAR64(a, -n);
	}
	int output[INT64_LEN];
	/// case 1: 00000000_00000001 << 32
	///       = 00000001_00000000
	/// case 2: 00000000_01010101 << 8
	///       = 00000001_01010100
	/// case 3: 00000000_01010101 << 16
	///       = 00000101_01010000
	if( n < INT64_BIT_LEN ) {
		if( n >= INT32_BIT_LEN ) {
			output[1] = a[0] << (n - INT32_BIT_LEN);
			output[0] = 0;
		} else {
			output[1] = (a[1] << n) | (a[0] >>> (INT32_BIT_LEN - n));
			output[0] = a[0] << n;
		}
	}
	return output;
}
/// Shift Arithmetic Right
stock int[] SAR64(int a[INT64_LEN], int n) {
	if( n < 0 ) {
		return SAL64(a, -n);
	}
	int output[INT64_LEN];
	if( n < INT64_BIT_LEN ) {
		if( n >= INT32_BIT_LEN ) {
			output[0] = a[1] >> (n - INT32_BIT_LEN);
			output[1] = 0;
		} else {
			output[1] = (a[1] >> n);
			output[0] = (a[0] >> n) | (a[0] << (INT32_BIT_LEN - n));
		}
	} else if( a[1] < 0 ) {
		output[0] = -1;
		output[1] = -1;
	}
	return output;
}
/// Shift Logical Right
stock int[] SLR64(int a[INT64_LEN], int n) {
	if( n < 0 ) {
		return SAL64(a, -n);
	}
	int output[INT64_LEN];
	if( n < INT64_BIT_LEN ) {
		if( n >= INT32_BIT_LEN ) {
			output[0] = a[1] >>> (n - INT32_BIT_LEN);
			output[1] = 0;
		} else {
			output[1] = (a[1] >>> n);
			output[0] = (a[0] >>> n) | (a[1] << (INT32_BIT_LEN - n));
		}
	}
	return output;
}


stock bool UI64LT(int x[INT64_LEN], int y[INT64_LEN]) {
	bool A = x[1] != 0;
	bool B = y[1] != 0;
	if( A==B ) {
		int i = view_as< int >(x[1] != y[1]);
		return UInt32LT(x[i], y[i]);
	}
	return !A && B;
}
stock bool UI64GT(int x[INT64_LEN], int y[INT64_LEN]) { return  UI64LT(y,x); }
stock bool UI64GE(int x[INT64_LEN], int y[INT64_LEN]) { return !UI64LT(x,y); }
stock bool UI64LE(int x[INT64_LEN], int y[INT64_LEN]) { return !UI64GT(x,y); }


stock bool I64LT(int x[INT64_LEN], int y[INT64_LEN]) {
	bool A = x[1] < 0;
	bool B = y[1] < 0;
	if( A==B ) {
		return UI64LT(x, y);
	}
	return A && !B;
}
stock bool I64GT(int x[INT64_LEN], int y[INT64_LEN]) { return  I64LT(y,x); }
stock bool I64GE(int x[INT64_LEN], int y[INT64_LEN]) { return !I64LT(x,y); }
stock bool I64LE(int x[INT64_LEN], int y[INT64_LEN]) { return !I64GT(x,y); }
stock bool I64EQ(int x[INT64_LEN], int y[INT64_LEN]) { return x[0]==y[0] && x[1]==y[1]; }
stock bool I64NE(int x[INT64_LEN], int y[INT64_LEN]) { return !I64EQ(x,y); }


stock int MinI32(int a, int b) {
	return( a < b )? a : b;
}
stock int MinU32(int a, int b) {
	return( UInt32LT(a,b) )? a : b;
}
stock int[] MinI64(int a[INT64_LEN], int b[INT64_LEN]) {
	return( I64LT(a,b) )? a : b;
}
stock int[] MinU64(int a[INT64_LEN], int b[INT64_LEN]) {
	return( UI64LT(a,b) )? a : b;
}

stock int MaxI32(int a, int b) {
	return( a > b )? a : b;
}
stock int MaxU32(int a, int b) {
	return( UInt32GT(a,b) )? a : b;
}
stock int[] MaxI64(int a[INT64_LEN], int b[INT64_LEN]) {
	return( I64GT(a,b) )? a : b;
}
stock int[] MaxU64(int a[INT64_LEN], int b[INT64_LEN]) {
	return( UI64GT(a,b) )? a : b;
}

stock int ClampI32(int v, int l, int h) {
	return MinI32(MaxI32(v, l), h);
}
stock int ClampU32(int v, int l, int h) {
	return MinU32(MaxU32(v, l), h);
}
stock int[] ClampI64(int v[INT64_LEN], int l[INT64_LEN], int h[INT64_LEN]) {
	return MinI64(MaxI64(v, l), h);
}
stock int[] ClampU64(int v[INT64_LEN], int l[INT64_LEN], int h[INT64_LEN]) {
	return MinU64(MaxU64(v, l), h);
}

stock int[] AbsI64(int a[INT64_LEN]) {
	if( I64LT(a, {0,0}) ) {
		return Neg64(a);
	}
	return a;
}

stock bool TestBit64(int i[INT64_LEN], int idx) {
	idx = ClampI32(idx, 0, INT64_BIT_LEN-1);
	return (i[idx >>> INT32_BIT_LEN_IDX] & (1 << (idx & (INT32_BIT_LEN-1)))) != 0;
}
stock void SetBit64(int i[INT64_LEN], int idx) {
	idx = ClampI32(idx, 0, INT64_BIT_LEN-1);
	i[idx >>> INT32_BIT_LEN_IDX] |= (1 << (idx & (INT32_BIT_LEN-1)));
}
stock void ToggleBit64(int i[INT64_LEN], int idx) {
	idx = ClampI32(idx, 0, INT64_BIT_LEN-1);
	i[idx >>> INT32_BIT_LEN_IDX] ^= (1 << (idx & (INT32_BIT_LEN-1)));
}
stock void ClearBit64(int i[INT64_LEN], int idx) {
	idx = ClampI32(idx, 0, INT64_BIT_LEN-1);
	i[idx >>> INT32_BIT_LEN_IDX] &= ~(1 << (idx & (INT32_BIT_LEN-1)));
}


stock int[] Add64(int x[INT64_LEN], int y[INT64_LEN], int carry_in=0, int& carry_out=0) {
	int output[INT64_LEN];
	output[0] = x[0] + y[0] + carry_in;
	int carry = UInt32LT(output[0], MaxI32(x[0], y[0]));
	output[1] = x[1] + y[1] + carry;
	carry_out = carry;
	return output;
}
stock int[] Neg64(int a[INT64_LEN]) {
	int one[INT64_LEN] = {1, 0};
	int output[INT64_LEN];
	output = Not64(a);
	output = Add64(output, one);
	return output;
}
stock int[] Sub64(int x[INT64_LEN], int y[INT64_LEN], int borrow_in=0, int& borrow_out=0) {
	int output[INT64_LEN];
	int negy[INT64_LEN]; negy = Neg64(y);
	output = Add64(x, negy, borrow_in, borrow_out);
	borrow_out = !borrow_out;
	return output;
}

stock int[] Mul64(int x[INT64_LEN], int y[INT64_LEN], int& carry_out=0) {
	int c[INT64_LEN];
	if( I64EQ(x, {0,0}) || I64EQ(y, {0,0}) ) {
		return c;
	}
	int a[INT64_LEN]; a = x;
	int b[INT64_LEN]; b = y;
	bool neg = I64LT(a, {0,0}) ^ I64LT(b, {0,0});
	a = AbsI64(a);
	b = AbsI64(b);
	while( !I64EQ(b, {0,0}) ) {
		if( I64GT(And64(b, {0x1,0}), {0,0}) ) {
			c = Add64(c,a,_,carry_out);
		}
		a = SAL64(a, 1);
		b = SLR64(b, 1);
	}
	if( neg ) {
		c = Neg64(c);
	}
	return c;
}
stock int[] DivMod64(int x[INT64_LEN], int y[INT64_LEN], int r[INT64_LEN]={0,0}) {
	int output[INT64_LEN];
	if( I64EQ(y,{0,0}) ) {
		/// div by 0.
		output = I64FromParts(-1, -1);
		return output;
	} else if( I64EQ(y,{1,0}) ) {
		return x;
	}
	r = x;
	while( I64GE(r, y) ) {
		r = Sub64(r, y);
		output = Add64(output, {1,0});
	}
	return output;
}
stock int[] Pow64(int b[INT64_LEN], int p[INT64_LEN]) {
	int output[INT64_LEN];
	if( I64LT(p, {0,0}) ) {
		return output;
	}
	output[0]++;
	if( I64EQ(p, {0,0}) || I64EQ(b, {1,0}) ) {
		return output;
	} else if( I64GE(p, {64,0}) ) {
		output = I64FromParts(0x7fffffff, 0xffffffff);
		return output;
	}
	for( int i[INT64_LEN]; I64LT(i, p); i = Add64(i, {1,0}) ) {
		output = Mul64(output, b);
	}
	return output;
}

stock int[] ByteSwap64(int x[INT64_LEN]) {
	int output[INT64_LEN];
	/// 0x0102AABB_CCDDEEFF
	/// 0xFFEEDDCC_BBAA0201
	output[0] = (x[1] >>> 24) | ((x[1]&0xFF0000) >>> 8) | ((x[1]&0xFF00) << 8) | ((x[1]&0xFF) << 24);
	output[1] = (x[0] >>> 24) | ((x[0]&0xFF0000) >>> 8) | ((x[0]&0xFF00) << 8) | ((x[0]&0xFF) << 24);
	return output;
}

stock int[] BitReverse64(int x[INT64_LEN]) {
	int output[INT64_LEN];
	/// last bit is 1st, 1st is last bit.
	for( int i=0; i < INT32_BIT_LEN; i++ ) {
		output[0] |= (((x[1] >>> i) & 1) != 0) << (INT32_BIT_LEN - 1 - i);
		output[1] |= (((x[0] >>> i) & 1) != 0) << (INT32_BIT_LEN - 1 - i);
	}
	return output;
}

stock int[] ROL64(int x[INT64_LEN], int count) {
	int output[INT64_LEN];
	int mask = INT64_BIT_LEN - 1;
	count &= mask;
	int l[INT64_LEN]; l = SAL64(x, count);
	int r[INT64_LEN]; r = SLR64(x, -count & mask);
	output = Or64(l, r);
	return output;
}
stock int[] ROR64(int x[INT64_LEN], int count) {
	int output[INT64_LEN];
	int mask = INT64_BIT_LEN - 1;
	count &= mask;
	int l[INT64_LEN]; l = SLR64(x, count);
	int r[INT64_LEN]; r = SAL64(x, -count & mask);
	output = Or64(l, r);
	return output;
}

/// Count Leading Zeroes and Count Trailing Zeroes.
stock int CLZ64(int x[INT64_LEN]) {
	if( I64EQ(x,{0,0}) ) {
		return INT64_BIT_LEN;
	}
	int count = 0;
	int a[INT64_LEN]; a = x;
	while( !TestBit64(a, (INT64_BIT_LEN-1) - count) ) {
		count++;
	}
	return count;
}
stock int CTZ64(int x[INT64_LEN]) {
	if( I64EQ(x,{0,0}) ) {
		return INT64_BIT_LEN;
	}
	int r[INT64_LEN]; r = Sub64(x, {1,0});
	int o[INT64_LEN]; o = Xor64(r, o);
	return PopCount64(o) - 1;
}