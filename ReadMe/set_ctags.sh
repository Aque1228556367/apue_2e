#!/bin/bash

#
# File: ctags.sh
# Author: zhankunlin
# Date: 2011-11-30
# Desc: ctags ctags 生成系统库，存放于 ~/.vim/systags 文件中
# 原链接：http://blog.csdn.net/zklth/article/details/7027798
#

mkdir -p ~/.vim;

ctags -I __THROW -I __attribute_pure__ -I __nonnull -I __attribute__ \
--file-scope=yes \
--langmap=c:+.h \
--languages=c,c++ \
--links=yes \
--c-kinds=+p \
--c++-kinds=+p \
--fields=+iaS \
--extra=+q  \
-f ~/.vim/systags \
/usr/include/* \
/usr/include/sys/* \
/usr/include/bits/*  \
/usr/include/netinet/* \
/usr/include/arpa/*

printf '\n\n"ctags""========================="set tags+=~/.vim/systags"========================="' >> ~/.vimrc
