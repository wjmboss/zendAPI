// Copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by zzu_softboy on 2017/08/01.

#ifndef ZAPI_VM_INTERNAL_ABSTRACT_CLASS_PRIVATE_H
#define ZAPI_VM_INTERNAL_ABSTRACT_CLASS_PRIVATE_H

#include "zapi/Global.h"
#include <string>
#include <list>
#include <map>

namespace zapi
{

namespace lang
{
class Method;
class Interface;
class Property;
class Member;
} // lang

namespace vm
{

class AbstractClass;

namespace internal
{

using zapi::lang::ClassType;
using zapi::lang::Method;
using zapi::lang::Member;
using zapi::lang::Property;
using zapi::lang::Modifier;
using zapi::lang::ClassType;

class AbstractClassPrivate
{
public:
   AbstractClassPrivate(const char *classname, ClassType type);
   zend_class_entry *initialize(const std::string &ns);
   std::unique_ptr<zend_function_entry[]> &getMethodEntries();
   // php class system facility static handle methods
   static zend_object *createObject(zend_class_entry *entry);
   static zend_object *cloneObject(zval *value);
   static void destructObject(zend_object *object);
   static void freeObject(zend_object *object);
   
   static zend_function *getStaticMethod(zend_class_entry *entry, zend_string *methodName);
public:
   std::unique_ptr<AbstractClass> m_apiPtr;
   std::string m_name;
   ClassType m_type = ClassType::Regular;
   zend_class_entry *m_classEntry = nullptr;
   std::unique_ptr<zend_function_entry[]> m_methodEntries;
   zend_object_handlers m_handlers;
   std::list<std::shared_ptr<AbstractClassPrivate>> m_interfaces;
   std::list<std::shared_ptr<Method>> m_methods;
   std::list<std::shared_ptr<Member>> m_members;
   std::map<std::string, std::shared_ptr<Property>> m_properties;
   std::shared_ptr<AbstractClassPrivate> m_parent;
   bool m_intialized = false;
   zend_string *m_self = nullptr;
};

} // internal
} // vm
} // zapi

#endif // ZAPI_VM_INTERNAL_ABSTRACT_CLASS_PRIVATE_H