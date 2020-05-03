-- 常用的数据类型--

--type--
	-- int 
	tinyint
	smallint
	mediumint -- 3个字节, 一般用于rbg像素点存储
	int -- 一般是使用int居多
	bigint

	-- double 
	float
	double -- 一般使用double居多
	decimal -- 一般用于对精度要求高的数据, 比如说money, 必须指定decimal(M, N), M表示有效位数, N表示小数位数

	-- varchar 
	char -- 一般存储定长字符串, 比如说身份证
	varchar -- 一般使用varchar存储字符串, 其空间利用率高, 查询效率略逊色于char
	text -- 一般存储大量文本数据, 比如说文章
	blob -- 一般存储二进制数据, 比如说文件, 音频, 视频

	-- date 
	date -- 一般用于存储年月日, 比如说生日
	datetime
	timestamp -- 一般用于获取当前时间

	-- string 
	enum -- 一般用于多选一, 比如说性别
	set -- 多选多, 使用的比较少

-- varchar的最大长度 --
  -- 影响varchar最大长度的因素: 存储规则, 字符编码, sql行长度
	-- maxLen = (65535-null标识-长度标识-其他字段长度)/字符大小
  -- 1. 存储规则
    -- varchar用1个字节来标识null, 1-2个字节标识数据长度
  -- 2. 字符编码
    -- 根据字符编码不同, 每个字符所占的字节大小不同
	  -- utf8: maxLen = (65535-1-2)/3 = 21844
	  -- gbk: maxLen = (65535-1-2)/2 = 32766
	  -- ascii: maxLen = (65535-1-1)/1 = 65533
  -- 3. sql行长度
    -- sql行长度规定不超多65535, 也就是表中字段的总长度
