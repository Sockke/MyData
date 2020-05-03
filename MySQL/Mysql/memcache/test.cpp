// 1.MySQL作为持久化存储，在互联网IT行业被广泛使用。
// 但MySQL由于其性能受限于磁盘性能，逐渐无法满足web2.0时代大型互联网服务的性能要求。
//
// Memcache作为内存缓存服务，以其高性能著称，逐步被众多互联网公司引入以提高吞吐量
// 以及响应性能。
//
// 互联网常用的存储架构选型是Memcache作为缓存 + MySQL作为数据库，
// 假设业务请求量为100万/s，MySQL可支持10万/s的qps。

// 1.Memcache需要最低满足多少命中率？
//  (100 - 10) / 100 = %90
// 2.假设单个K-V是200Byte，估算Memcache带宽？
//  考虑不仅要从Memcache中读取数据, 还要考虑向Memcache写入数据
//  (200Byte * 1000000) = 190.7M/s
// 3.每天访问过Memcache的key总数（去重）共1亿条，估算Memcache需要消耗多少内存？ 
//  如果Memcache内存无上限, 还是需要考虑向Memcache写入数据
//  (200 * 100000000) = 18.6G
