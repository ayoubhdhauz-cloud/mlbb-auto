#include "Il2cpp.h"
#import <mach-o/dyld.h>
#import <pthread/pthread.h>
#import <thread>
#include <codecvt>
#include <dlfcn.h>
#include <math.h>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
namespace {
    const void *(*il2cpp_assembly_get_image)(const void *assembly);
    void *(*il2cpp_domain_get)();
    void **(*il2cpp_domain_get_assemblies)(const void *domain, size_t *size);
    const char *(*il2cpp_image_get_name)(void *image);
    void *(*il2cpp_class_from_name)(const void *image, const char *namespaze, const char *name);
    void *(*il2cpp_class_get_field_from_name)(void *klass, const char *name);
    void *(*il2cpp_class_get_method_from_name)(void *klass, const char *name, int argsCount);
    size_t (*il2cpp_field_get_offset)(void *field);
    void (*il2cpp_field_static_get_value)(void *field, void *value);
    void (*il2cpp_field_static_set_value)(void *field, void *value);
    void* (*il2cpp_image_get_class)(void *image, size_t index);
    size_t (*il2cpp_image_get_class_count)(void* Klass);
    size_t (*il2cpp_class_num_fields)(void* Klass);
    const void* (*il2cpp_class_get_image)(const void* Klass);
    const char *(*il2cpp_class_get_name)(void* Klass);
    const char *(*il2cpp_class_get_namespace)(void* Klass); 
    void* (*il2cpp_class_get_fields)(void* Klass,void** iter);
    void* (*il2cpp_class_get_parent)(void* Klass);
    const char *(*il2cpp_field_get_name)(void *field);
    void *(*il2cpp_array_new)(void *elementTypeInfo, size_t length);
    uint16_t *(*il2cpp_string_chars)(void *str);
    Il2CppString *(*il2cpp_string_new)(const char *str);
    Il2CppString *(*il2cpp_string_new_utf16)(const wchar_t *str, int32_t length);
    char *(*il2cpp_type_get_name)(void *type);
    void* (*il2cpp_method_get_param)(void *method, uint32_t index);
    void* (*il2cpp_class_get_methods)(void *klass, void* *iter);
    const char* (*il2cpp_method_get_name)(void *method);
    void *(*il2cpp_object_new)(void *klass);
}
// =========================================================================== //
void Attach()
{
    il2cpp_assembly_get_image = (const void *(*)(const void *)) dlsym(RTLD_DEFAULT, "il2cpp_assembly_get_image");
    il2cpp_domain_get = (void *(*)()) dlsym(RTLD_DEFAULT, "il2cpp_domain_get");
    il2cpp_domain_get_assemblies = (void **(*)(const void* , size_t*)) dlsym(RTLD_DEFAULT, "il2cpp_domain_get_assemblies");
    il2cpp_image_get_name = (const char *(*)(void *)) dlsym(RTLD_DEFAULT, "il2cpp_image_get_name");
    il2cpp_class_from_name = (void* (*)(const void*, const char*, const char *)) dlsym(RTLD_DEFAULT, "il2cpp_class_from_name");
    il2cpp_class_get_field_from_name = (void* (*)(void*, const char *)) dlsym(RTLD_DEFAULT, "il2cpp_class_get_field_from_name");
    il2cpp_class_get_method_from_name = (void* (*)(void *, const char*, int)) dlsym(RTLD_DEFAULT, "il2cpp_class_get_method_from_name");
    il2cpp_field_get_offset = (size_t (*)(void *)) dlsym(RTLD_DEFAULT, "il2cpp_field_get_offset");
    il2cpp_field_static_get_value = (void (*)(void*, void *)) dlsym(RTLD_DEFAULT, "il2cpp_field_static_get_value");
    il2cpp_field_static_set_value = (void (*)(void*, void *)) dlsym(RTLD_DEFAULT, "il2cpp_field_static_set_value");
    il2cpp_image_get_class = reinterpret_cast<void *(*)(void *, size_t)>(dlsym(RTLD_DEFAULT, "il2cpp_image_get_class"));
    il2cpp_image_get_class_count = reinterpret_cast<size_t (*)(void *)>(dlsym(RTLD_DEFAULT, "il2cpp_image_get_class_count"));
    il2cpp_class_num_fields = reinterpret_cast<size_t (*)(void *)>(dlsym(RTLD_DEFAULT, "il2cpp_class_num_fields"));
    il2cpp_class_get_image = reinterpret_cast<const void *(*)(const void *)>(dlsym(RTLD_DEFAULT, "il2cpp_class_get_image"));
    il2cpp_class_get_name = reinterpret_cast<const char *(*)(void *)>(dlsym(RTLD_DEFAULT, "il2cpp_class_get_name"));
    il2cpp_class_get_namespace = reinterpret_cast<const char *(*)(void *)>(dlsym(RTLD_DEFAULT, "il2cpp_class_get_namespace"));
    il2cpp_class_get_fields = reinterpret_cast<void *(*)(void *, void **)>(dlsym(RTLD_DEFAULT, "il2cpp_class_get_fields"));
    il2cpp_class_get_parent = reinterpret_cast<void *(*)(void *)>(dlsym(RTLD_DEFAULT, "il2cpp_class_get_parent"));
    il2cpp_field_get_name = reinterpret_cast<const char *(*)(void *)>(dlsym(RTLD_DEFAULT, "il2cpp_field_get_name"));
    il2cpp_array_new = (void *(*)(void*, size_t)) dlsym(RTLD_DEFAULT, "il2cpp_array_new");
    il2cpp_string_chars = (uint16_t *(*)(void*)) dlsym(RTLD_DEFAULT, "il2cpp_string_chars");
    il2cpp_string_new = (Il2CppString *(*)(const char *)) dlsym(RTLD_DEFAULT, "il2cpp_string_new");
    il2cpp_string_new_utf16 = (Il2CppString *(*)(const wchar_t *, int32_t)) dlsym(RTLD_DEFAULT, "il2cpp_string_new");
    il2cpp_type_get_name = (char *(*)(void *)) dlsym(RTLD_DEFAULT, "il2cpp_type_get_name");
    il2cpp_method_get_param = (void *(*)(void *, uint32_t)) dlsym(RTLD_DEFAULT, "il2cpp_method_get_param");
    il2cpp_class_get_methods = (void *(*)(void *, void **)) dlsym(RTLD_DEFAULT, "il2cpp_class_get_methods");
    il2cpp_method_get_name = (const char *(*)(void *)) dlsym(RTLD_DEFAULT, "il2cpp_method_get_name");
    il2cpp_object_new = (void *(*)(void *)) dlsym(RTLD_DEFAULT, "il2cpp_object_new");
    
}
// =========================================================================== //
typedef unsigned short UTF16;
typedef wchar_t UTF32;
typedef char UTF8;

int is_surrogate(UTF16 uc) {
    return (uc - 0xd800u) < 2048u;
}

int is_high_surrogate(UTF16 uc) {
    return (uc & 0xfffffc00) == 0xd800;
}

int is_low_surrogate(UTF16 uc) {
    return (uc & 0xfffffc00) == 0xdc00;
}

UTF32 surrogate_to_utf32(UTF16 high, UTF16 low) {
    return (high << 10) + low - 0x35fdc00;
}

const char* utf16_to_utf8(const UTF16* source, size_t len) {
    std::u16string s(source, source + len);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    std::string temp = convert.to_bytes(s);
    char* cstr = new char[temp.length() + 1];
    std::strcpy(cstr, temp.c_str());
    return cstr;
    //return convert.to_bytes(s).c_str();
}

const wchar_t* utf16_to_utf32(const UTF16* source, size_t len) {
    auto output = new UTF32[len + 1];

    for (int i = 0; i < len; i++) {
        const UTF16 uc = source[i];
        if (!is_surrogate(uc)) {
            output[i] = uc;
        }
        else {
            if (is_high_surrogate(uc) && is_low_surrogate(source[i]))
                output[i] = surrogate_to_utf32(uc, source[i]);
            else
                output[i] = L'?';
        }
    }

    output[len] = L'\0';
    return output;
}
// =========================================================================== //
const char* Il2CppString::CString() {
    return utf16_to_utf8(&this->start_char, this->length);
}

const wchar_t* Il2CppString::WCString() {
    return utf16_to_utf32(&this->start_char, this->length);
}

Il2CppString *Il2CppString::Create(const char *s)
{
    return il2cpp_string_new(s);
}

Il2CppString *Il2CppString::Create(const wchar_t *s, int len)
{
    return il2cpp_string_new_utf16(s, len);
}
// =========================================================================== //
void *Il2CppGetImageByName(const char *image) {
    size_t size;
    void **assemblies = il2cpp_domain_get_assemblies(il2cpp_domain_get(), &size);
    for(int i = 0; i < size; ++i)
    {
        void *img = (void *)il2cpp_assembly_get_image(assemblies[i]);

        const char *img_name = il2cpp_image_get_name(img);

        if(strcmp(img_name, image) == 0)
        {
            return img;
        }
    }
    return nullptr;
}
// ================================================================================================================ //
void *Il2CppGetClassType(const char *image, const char *namespaze, const char *clazz) {
    static std::map<std::string, void *> cache;

    std::string s = image;
    s += namespaze;
    s += clazz;

    if (cache.count(s) > 0)
        return cache[s];

    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
        return nullptr;
    }

    void *klass = il2cpp_class_from_name(img, namespaze, clazz);
    if(!klass) {
        size_t count = il2cpp_image_get_class_count(img);
        for (size_t i = 0; i < count; i++) {
            void *candidate = il2cpp_image_get_class(img, i);
            if (!candidate) break;
            const char *cname = il2cpp_class_get_name(candidate);
            if (cname && strcmp(cname, clazz) == 0) {
                cache[s] = candidate;
                NSLog(@"Found class %s via fallback scan (ns='%s')", clazz, namespaze ? namespaze : "NULL");
                return candidate;
            }
        }
        NSLog(@"Can't find class %s (namespace='%s')!", clazz, namespaze ? namespaze : "NULL");
        return nullptr;
    }

    cache[s] = klass;
    return klass;
}
// ================================================================================================================ //
void *Il2CppCreateClassInstance(const char *image, const char *namespaze, const char *clazz) {
    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
        return nullptr;
    }

    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    if(!klass) {
        NSLog(@"Can't find class %s!", clazz);
        return nullptr;
    }

    void *obj = il2cpp_object_new(klass);
    if(!obj)
    {
        NSLog(@"Can't create object for %s", clazz);
        return nullptr;
    }

    return obj;
}
// ================================================================================================================ //
void* Il2CppCreateArray(const char *image, const char *namespaze, const char *clazz, size_t length) {
    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
        return nullptr;
    }
    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    if(!klass) {
        NSLog(@"Can't find class %s!", clazz);
        return nullptr;
    }

    return il2cpp_array_new(klass, length);
}
// ================================================================================================================ //
void Il2CppGetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void *output) {
    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
            return;
    }
    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    if(!klass) {
        NSLog(@"Can't find class %s for field %s!", clazz, name);
        return;
    }

    void *field = il2cpp_class_get_field_from_name(klass, name);
    if(!field) {
        NSLog(@"Can't find field %s in class %s!", name, clazz);
        return;
    }

    il2cpp_field_static_get_value(field, output);
}
// ================================================================================================================ //
void Il2CppSetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void* value) {
    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
        return;
    }
    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    if(!klass) {
        NSLog(@"Can't find class %s for field %s!", clazz, name);
        return;
    }

    void *field = il2cpp_class_get_field_from_name(klass, name);
    if(!field) {
        NSLog(@"Can't find field %s in class %s!", name, clazz);
        return;
    }

    il2cpp_field_static_set_value(field, value);
}
// ================================================================================================================ //
void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount) {
    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
        return nullptr;
    }

    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    if(!klass) {
        NSLog(@"Can't find class %s for method %s!", clazz, name);
        return nullptr;   
    }

    void **method = (void**)il2cpp_class_get_method_from_name(klass, name, argsCount);
    if(!method) {
        NSLog(@"Can't find method %s in class %s!", name, clazz);
        return nullptr;
    }
    NSLog(@"%s - [%s] %s::%s: %p", image, namespaze, clazz, name, *method);
    return *method;
}

bool Il2CppHookImpl(const char *image, const char *namespaze, const char *clazz, void* hook, void* orig, const char * name, int cnttt)
{
    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    MethodInfo* method = (MethodInfo*)il2cpp_class_get_method_from_name(klass, name, cnttt);

    if (!method && !hook) { return false; };

    if (orig) { *(void**)orig = (void*)method->methodPointer; }

    method->methodPointer = hook;

    return true;
}

// ================================================================================================================ //
void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, char** args, int argsCount) {
    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
        return 0;
    }

    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    if(!klass) {
        NSLog(@"Can't find class %s for method %s!", clazz, name);
        return 0;
    }

    void *iter = 0;

    int score = 0;

    void **method = (void**) il2cpp_class_get_methods(klass, &iter);
    while(method) {
        const char *fname = il2cpp_method_get_name(method);
        if(strcmp(fname, name) == 0) {
            for (int i = 0; i < argsCount; i++) {
                void *arg = il2cpp_method_get_param(method, i);
                if (arg) {
                    const char *tname = il2cpp_type_get_name(arg);
                    if (strcmp(tname, args[i]) == 0) {
                        score++;
                    } else {
                        NSLog(@"Argument at index %d didn't matched requested argument!\n\tRequested: %s\n\tActual: %s\nnSkipping function...", i, args[i], tname);
                        score = 0;
goto skip;
                    }
                }
            }
        }
        skip:

        if(score == argsCount)
        {
            NSLog(@"%s - [%s] %s::%s: %p", image, namespaze, clazz, name, *method);
            return *method;
        }

        method = (void **) il2cpp_class_get_methods(klass, &iter);
    }
    NSLog(@"Cannot find function %s in class %s!", name, clazz);
    return 0;
}
// ================================================================================================================ //
size_t Il2CppGetFieldOffset(const char *image, const char *namespaze, const char *clazz, const char *name) {
    
    void *img = Il2CppGetImageByName(image);
    if(!img) {
        NSLog(@"Can't find image %s!", image);
        return -1;
    }
    void *klass = Il2CppGetClassType(image, namespaze, clazz);
    if(!klass) {
        NSLog(@"Can't find class %s for field %s!", clazz, name);
        return -1;
    }

    void *field = il2cpp_class_get_field_from_name(klass, name);
    if(!field) {
        NSLog(@"Can't find field %s in class %s!", name, clazz);
        return -1;
    }
    auto result = il2cpp_field_get_offset(field);
    NSLog(@"%s - [%s] %s::%s: %p", image, namespaze, clazz, name, (void *) result);
    return result;
}
// ================================================================================================================ //
bool Il2CppIsAssembliesLoaded() {
    size_t size;
    void **assemblies = il2cpp_domain_get_assemblies(il2cpp_domain_get(), &size);

    return size != 0 && assemblies != 0;
}
// ================================================================================================================ //
void* Il2CppGetSingleton(const char *dllfilename, const char *namespaze, const char *className)
{
    void* dllfile = Il2CppGetImageByName(dllfilename);
    if(dllfile)
    {
        void* getClass = il2cpp_class_from_name(dllfile,namespaze,className);
        if(getClass)
        {
            void* parentclass = il2cpp_class_get_parent(getClass);
            int fieldsCount = il2cpp_class_num_fields(parentclass);
            if (fieldsCount > 0) 
            {
                void* iterator = NULL; 
                void* field = NULL;
                while ((field = il2cpp_class_get_fields(parentclass, &iterator)) != NULL)
                {
                    if(field ==NULL) break;
                    const char* fieldName = il2cpp_field_get_name(field);
                    // if (strcmp(fieldName, "s_instance") == 0)
                    if (strstr(fieldName, "_instance") != NULL)
                    {
                        uint64_t myFieldValue = 0;
                        il2cpp_field_static_get_value(field,(void*)&myFieldValue);
                        return (void*)myFieldValue;
                    }
                }
            }
        }
    }
    return nullptr;
}
void* get_offset(const char *dllfilename, const char *namespaze, const char *className, const char *methodName, int argsCount) {
    return Il2CppGetMethodOffset(dllfilename, namespaze, className, methodName, argsCount);
}
size_t getFieldOffset(const char *dllFilename, const char *namespaceName, const char *className, const char *fieldName) {
    return Il2CppGetFieldOffset(dllFilename, namespaceName, className, fieldName);
}
int GetObscuredIntValue(uint64_t location) {
    int cryptoKey = *(int*)location;
    int obfuscatedValue = *(int*)(location + 0x4);

    return obfuscatedValue ^ cryptoKey;
}

int GetObscuredBoolValue(uint64_t location) {
    int cryptoKey = *(int*)(location + 0x8);
    int obfuscatedValue = *(int*)(location + 0xC);
    obfuscatedValue ^= cryptoKey;
    return obfuscatedValue;
}

/*
Set the real value of an ObscuredInt.
Parameters:
    - location: the location of the ObscuredInt
    - value: the value we're setting the ObscuredInt to
*/
void SetObscuredIntValue(uint64_t location, int value) {
    int cryptoKey = *(int*)location;

    *(int*)(location + 0x4) = value ^ cryptoKey;
}

/*
Get the real value of an ObscuredFloat.
Parameters:
    - location: the location of the ObscuredFloat
*/
float GetObscuredFloatValue(uint64_t location) {
    int cryptoKey = *(int*)location;
    int obfuscatedValue = *(int*)(location + 0x4);

    /* use this intfloat to set the integer representation of our parameter value, which will also set the float value */
    intfloat IF;
    IF.i = obfuscatedValue ^ cryptoKey;

    return IF.f;
}

/*
Set the real value of an ObscuredFloat.
Parameters:
    - location: the location of the ObscuredFloat
    - value: the value we're setting the ObscuredFloat to
*/
void SetObscuredFloatValue(uint64_t location, float value) {
    int cryptoKey = *(int*)location;

    /* use this intfloat to get the integer representation of our parameter value */
    intfloat IF;
    IF.f = value;

    /* use this intfloat to generate our hacked ObscuredFloat */
    intfloat IF2;
    IF2.i = IF.i ^ cryptoKey;

    *(float*)(location + 0x4) = IF2.f;
}