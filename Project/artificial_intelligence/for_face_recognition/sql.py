'''
    sqlite的操作
'''
import sqlite3

class Sqlite(object):
    def __init__(self, database='images_dataset.db', table='dataset'):
        '''构造函数'''
        self.database = database
        self.table = table
        self.conn = None
        
    def connect(self):
        '''连接数据库'''
        self.conn = sqlite3.connect(self.database)

    def modify(self, sql):
        '''增删改'''
        cursor = self.conn.cursor()
        cursor.execute(sql)
        self.conn.commit()
        cursor.close()

    def query(self, sql):
        '''查'''
        cursor = self.conn.cursor()
        cursor.execute(sql)
        self.conn.commit()
        data = cursor.fetchall()
        cursor.close()
        return data

    
