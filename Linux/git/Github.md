## Github

#### Github 介绍

```

```

#### git 客户端环境配置

```shell
# 1. 配置ssh通信用的公私钥
$ ssh-keygen -t -rsa -C "1109008311@qq.com"
# 2. 找到id_rsa.pub公钥文件添加到GitHub ssh配置中
将id_rsa.pub中的内容拷贝到GitHub->setting->SSH and GPG keys->new SSH key
# 3. 验证客户端能否与GitHub通过SSH正常通信
$ ssh -T git@github.com
# 4. 配置邮箱和用户名, 用户提交会携带信息(通过git log查看提交信息)
$ git config --global user.name "sockke"
$ git config --global user.email "1109008311@qq.com"
```

#### git 常用命令

```shell
# 将远程仓库的文件拉取到本地仓库, 在本地会创建2个东西, 分别是远程仓库的名称origin, 默认分支master
# 本地的master追踪远程仓库的origin/master
$ git clone ssh远程仓库地址
```

```shell
# 查看本地仓库的状态
$ git status
# 将工作区的工程添加到git暂存区
$ git add ./main.cpp
# 将git暂存区的工程提交到本地仓库的分支上
$ git commit -m "project"
# 将git本地仓库上添加的工程推送到远程仓库的master分支
# $ git push origin master:master  # master(本地分支):master(远程分支)
$ git push origin master
```

```shell
# 将远程仓库的工程更新拉取到本地仓库
$ git pull
```

#### git 撤销命令

```shell
# 将工作区修改的工程 撤销
$ git checkout --main.cpp
```

```shell
# 将暂存区中添加的工程 撤销
$ git reset HEAD main.cpp
```

```shell
# 将本地仓库中提交的工程 撤销
# 查看最新版本及以前的commit id
$ git log
# 修改HEAD指针回退到某个版本
$ git reset --hard commit-id

# 将本地仓库中提交的工程 反撤销
# 查看所有版本的commit id
$ git reflog
# 修改HEAD指针前进到某个版本
$ git reset --hard commit-id
```

```shell
# 将推送到远程仓库的工程 撤销
# 查看本地最新版本及之前的commit id
$ git log
# 修改HEAED指针回退到某个版本
$ git reset --hard commit-id
# 将落后的版本强制推送到远程仓库(保证没有其他人在远程仓库进行更新)
$ git push -f origin master
```

#### git 解决推送冲突

Gery与Tony通过git pull拉取远程仓库的更新,得到相同的版本v1.
Gehry在本地将v1更新到v2并推送到远程仓库, 推送成功
Tony在本地将v1更新到v3并推送到远程仓库, 推送冲突, git push失败

![](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200504123621791.png)

```shell
# 查看工作区工程的修改前后的对比信息
$ git diff HEAD -- main.cpp
```

```shell
# 从远程仓库拉取更新
$ git pull
# 如果多个版本的更新都是添加操作,git pull会进行自动合并更新
# 如果多个版本的更新修改的是同一段代码, git pull自动合并更新会失败, 需要手动修改工程并移除git添加的标记

# 推送合并后的版本
$ git push origin master
```

#### git 本地分支管理

```shell
# 查看本地分支
$ git branch
# 查看远程分支
$ git branch -r
# 查看所有分支
$ git branch -a
# 查看本地分支追踪的远程分支
$ git branch -vv
```

* 管理方式1, 切换到master分支进行分支合并, 然后再推送到远程仓库

```shell
# 在本地创建新分支, 并切换到该分支
$ git checkout -b myprojcet
# 将工作区的工程添加到暂存区
$ git add .
# 将暂存区的工程提交到本地仓库
$ git commit -m "..."
# 切换到master分支
$ git checkout master
# 拉取master分支的更新
$ git pull
# 将本地子分支的工程合并到master分支的仓库中
$ git merge myproject
# 将更新推送到远程仓库
$ git push origin master
# 删除本地分支
$ git branch -d myproject	
```

* 管理方式2, 在子分支推送时指定远程仓库的分支, 然后切换到master分支进行拉取更新

```shell
# 在本地创建新分支, 并切换到该分支
$ git checkout -b myprojcet
# 将工作区的工程添加到暂存区
$ git add .
# 将暂存区的工程提交到本地仓库
$ git commit -m "..."
# 将更新推送到远程仓库
$ git push origin myproject:master
# 切换到master分支
$ git checkout master
# 拉取master分支的更新
$ git pull
# 删除本地分支
$ git branch -d myproject
```

* 分支管理过程中造成的推送冲突(与上述普通推送引起冲突类似)

Gehry与Tony通过git pull从远程仓库拉取更新
Gehry在本地仓库将v2更新到v5并推送到远程仓库, 推送成功
Tony在本地创建分支subbranch, 在subbranch添加更新v3, 将v3合并到master更新到v4, 并推送到远程仓库, 推送失败

![](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200504171703859.png)



#### git 远程分支管理

公司中的项目一般是迭代开发的, 功能也是迭代添加的. 

如果原来远程分支master上的项目已经趋于稳定, 还想再进一步进行开发时, 一般就不会再在master分支上推送代码了, 而是在远程创建一个新的分支, 让新的开发工作在新的分支上, 这样就不会影响master分支上的项目了

```shell
# 在远程创建新分支, 比如叫dev
```

![image-20200505122707301](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200505122707301.png)

```shell
# 在本地创建新分支并追踪远程新创建的分支(本地分支名称尽量与远程分支名称相同, 这样push的时候可以少些代码)
$ git checkout -b dev origin/dev
# 将工程添加到暂存区
$ git add .
# 将暂存区中的工程提交到本地仓库
$ git commit -m "..."
# 将本地仓库中的工程推送到远程仓库
$ git push origin dev
```

