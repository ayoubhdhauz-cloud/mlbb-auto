//
// Created by aimar on 12/28/2019.
//
#include <mach-o/dyld.h>
#include <string>
#include <map>
#include <dlfcn.h>
#include <string>
#import <Foundation/Foundation.h>
typedef void(*Il2CppMethodPointer)();

struct MethodInfo;

struct VirtualInvokeData
{
    Il2CppMethodPointer methodPtr;
    const MethodInfo* method;
};

struct Il2CppType
{
    void* data;
    unsigned int bits;
};

struct Il2CppClass;

struct Il2CppObject
{
    Il2CppClass *klass;
    void *monitor;
};

union Il2CppRGCTXData
{
    void* rgctxDataDummy;
    const MethodInfo* method;
    const Il2CppType* type;
    Il2CppClass* klass;
};

struct Il2CppRuntimeInterfaceOffsetPair
{
    Il2CppClass* interfaceType;
    int32_t offset;
};
struct Il2CppClass_1
{
    void* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    Il2CppType byval_arg;
    Il2CppType this_arg;
    Il2CppClass* element_class;
    Il2CppClass* castClass;
    Il2CppClass* declaringType;
    Il2CppClass* parent;
    void *generic_class;
    void* typeDefinition;
    void* interopData;
    Il2CppClass* klass;
    void* fields;
    void* events;
    void* properties;
    void* methods;
    Il2CppClass** nestedTypes;
    Il2CppClass** implementedInterfaces;
    Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
};

struct Il2CppClass_2
{
    Il2CppClass** typeHierarchy;
    void *unity_user_data;
    uint32_t initializationExceptionGCHandle;
    uint32_t cctor_started;
    uint32_t cctor_finished;
    size_t cctor_thread;
    int32_t genericContainerIndex;
    uint32_t instance_size;
    uint32_t actualSize;
    uint32_t element_size;
    int32_t native_size;
    uint32_t static_fields_size;
    uint32_t thread_static_fields_size;
    int32_t thread_static_fields_offset;
    uint32_t flags;
    uint32_t token;
    uint16_t method_count;
    uint16_t property_count;
    uint16_t field_count;
    uint16_t event_count;
    uint16_t nested_type_count;
    uint16_t vtable_count;
    uint16_t interfaces_count;
    uint16_t interface_offsets_count;
    uint8_t typeHierarchyDepth;
    uint8_t genericRecursionDepth;
    uint8_t rank;
    uint8_t minimumAlignment;
    uint8_t naturalAligment;
    uint8_t packingSize;
    uint8_t bitflags1;
    uint8_t bitflags2;
};

struct Il2CppClass
{
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    VirtualInvokeData vtable[255];
};

typedef uintptr_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;
struct Il2CppArrayBounds
{
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
};

typedef void (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**, void*);
struct MethodInfo
{
    void* methodPointer;
    void* virtualMethodPointer;
    void* invoker_method;
    const char* name;
};

struct _Module__Fields {
};
struct _Module__c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    VirtualInvokeData vtable[32];
};
struct _Module__o {
    _Module__c *klass;
    void *monitor;
    _Module__Fields fields;
};
struct Locale_Fields {
};
struct Locale_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
};
struct Locale_c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    Locale_VTable vtable;
};
struct Locale_o {
    Locale_c *klass;
    void *monitor;
    Locale_Fields fields;
};
struct SR_Fields {
};
struct SR_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
};
struct SR_c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    SR_VTable vtable;
};
struct SR_o {
    SR_c *klass;
    void *monitor;
    SR_Fields fields;
};
struct Mono_Runtime_Fields {
};
struct Mono_Runtime_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
};
struct Mono_Runtime_c {
    Il2CppClass_1 _1;
    void* static_fields;
    Il2CppRGCTXData* rgctx_data;
    Il2CppClass_2 _2;
    Mono_Runtime_VTable vtable;
};
struct Mono_Runtime_o {
    Mono_Runtime_c *klass;
    void *monitor;
    Mono_Runtime_Fields fields;
};
/*
This struct can hold a native C# array. Credits to caoyin.

Think of it like a wrapper for a C array. For example, if you had Player[] players in a dump,
the resulting monoArray definition would be monoArray<void **> *players;

To get the C array, call getPointer.
To get the length, call getLength.
*/

/*
This struct represents a C# string. Credits to caoyin.

It is pretty straight forward. If you have this in a dump,

public class Player {
    public string username; // 0xC8
}

getting that string would look like this: monoString *username = *(monoString **)((uint64_t)player + 0xc8);

C# strings are UTF-16. This means each character is two bytes instead of one.

To get the length of a monoString, call getLength.
To get a NSString from a monoString, call toNSString.
To get a std::string from a monoString, call toCPPString.
To get a C string from a monoString, call toCString.
*/


/*
Turn a C string into a C# string!

This function is included in Unity's string class. There are two versions of this function in the dump, you want the one the comes FIRST.
The method signature is:

private string CreateString(PTR value);

Again, you want the FIRST one, not the second.
*/



/*

Create a native C# array with a starting length.

This one is kind of tricky to complete. I'm currently looking for an easier way to implement this.

The offsets you need are both found at String::Split(char separator[], int count). Go to that function in IDA and scroll down until you find something like this:

    TBNZ            W20, #0x1F, loc_101153944
    CMP             W20, #1
    B.EQ            loc_1011538B0
    CBNZ            W20, loc_101153924
    ADRP            X8, #qword_1026E0F20@PAGE
    NOP
    LDR             X19, [X8,#qword_1026E0F20@PAGEOFF]
    MOV             X0, X19
    BL              sub_101DD8AF8
    MOV             X0, X19
    MOV             W1, #0
    LDP             X29, X30, [SP,#0x30+var_10]
    LDP             X20, X19, [SP,#0x30+var_20]
    LDP             X22, X21, [SP+0x30+var_30],#0x30
    B               sub_101DD74E8

I filled in the locations here:

    TBNZ            W20, #0x1F, loc_101153944
    CMP             W20, #1
    B.EQ            loc_1011538B0
    CBNZ            W20, loc_101153924
    ADRP            X8, #qword_1026E0F20@PAGE
    NOP
    LDR             X19, [X8,#qword_1026E0F20@PAGEOFF] <-------- Whatever 1026E0F20 is in your game is your second location
    MOV             X0, X19
    BL              sub_101DD8AF8
    MOV             X0, X19
    MOV             W1, #0
    LDP             X29, X30, [SP,#0x30+var_10]
    LDP             X20, X19, [SP,#0x30+var_20]
    LDP             X22, X21, [SP+0x30+var_30],#0x30
    B               sub_101DD74E8                       <-------- Whatever 101DD74E8 is in your game is your first location
    
For example, if you wanted an array of 10 ints, you would do this: monoArray<int *> *integers = CreateNativeCSharpArray<int *>(10);

You can use any type with this!
*/

#if 0
template<typename T>
monoArray<T> *CreateNativeCSharpArray(int startingLength){
    monoArray<T> *(*IL2CPPArray_Create)(void *klass, int startingLength) = (monoArray<T> *(*)(void *, int))getRealOffset(/*FIRST LOCATION HERE*/);
    
    void *unkptr0 = *(void **)(ASLR_BIAS + /*SECOND LOCATION HERE*/);
    void *klass = *(void **)((uint64_t)unkptr0);
    
    monoArray<T> *arr = IL2CPPArray_Create(klass, startingLength);
    
    return arr;
}
#endif

/*
Here are some functions to safely get/set values for types from Anti Cheat Toolkit (https://assetstore.unity.com/packages/tools/utilities/anti-cheat-toolkit-10395)

I will add more to this as I go along.
*/
/*
Get the real value of an ObscuredInt.

Parameters:
    - location: the location of the ObscuredInt
*/

/*
Get the real value of an ObscuredVector3.

Parameters:
    - location: the location of the ObscuredVector3
*/


/*
Set the real value of an ObscuredVector3.

Parameters:
    - location: the location of the ObscuredVector3
    - value: the value we're setting the ObscuredVector3 to
*/
template<typename T> struct Il2CppArray {
    Il2CppClass *klass;
    void *monitor;
    void *bounds;
    int max_length;
    T m_Items[65535];

    int getLength() {
        return max_length;
    }

    T *getPointer() {
        return (T *)m_Items;
    }

    T &operator[](int i) {
        return m_Items[i];
    }

    T &operator[](int i) const {
        return m_Items[i];
    }
};

template<typename T>
using Array = Il2CppArray<T>;
template<typename T> struct Il2CppList {
    Il2CppClass *klass;
    void *unk1;
    Array<T> *items;
    int size;
    int version;

    T *getItems() {
        return items->getPointer();
    }

    int getSize() {
        return size;
    }

    int getVersion() {
        return version;
    }

    T &operator[](int i) {
        return items->m_Items[i];
    }

    T &operator[](int i) const {
        return items->m_Items[i];
    }

      std::vector<T> toCPPlist() {
        std::vector<T> ret;
        ret.reserve(size); // Reserve space in the vector for the items.

        for (int i = 0; i < size; i++) {
            ret.push_back(items->m_Items[i]);
        }

        return ret;
    }
};

template<typename T>
using List = Il2CppList<T>;
struct Il2CppString {
    Il2CppClass *klass;
    void *monitor;
    int32_t length;
    uint16_t start_char;

    const char *CString();

    const wchar_t *WCString();

    static Il2CppString *Create(const char *s);
    static Il2CppString *Create(const wchar_t *s, int len);

    int getLength() {
        return length;
    }
};

typedef Il2CppString String;



template<typename K, typename V> struct Il2CppDictionary {
    Il2CppClass *klass;
    void *unk1;
    Il2CppArray<int **> *table;
    Il2CppArray<void **> *linkSlots;
    Il2CppArray<K> *keys;
    Il2CppArray<V> *values;
    int touchedSlots;
    int emptySlot;
    int size;

    K *getKeys() {
        return keys->getPointer();
    }

    V *getValues() {
        return values->getPointer();
    }

    int getNumKeys() {
        return keys->getLength();
    }

    int getNumValues() {
        return values->getLength();
    }

    int getSize() {
        return size;
    }
};

template<typename K, typename V>
using Dictionary = Il2CppDictionary<K, V>;

void Attach();
void *Il2CppGetImageByName(const char *image);
void *Il2CppGetClassType(const char *image, const char *namespaze, const char *clazz);
void *Il2CppCreateClassInstance(const char *image, const char *namespaze, const char *clazz);
void* Il2CppCreateArray(const char *image, const char *namespaze, const char *clazz, size_t length);

void Il2CppGetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void *output);
void Il2CppSetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void* value);

void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount = 0);
void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, char** args, int argsCount);
bool Il2CppHookImpl(const char *image, const char *namespaze, const char *clazz, void* hook, void* orig, const char * name, int cnttt);

size_t Il2CppGetFieldOffset(const char *image, const char *namespaze, const char *clazz, const char *name);

bool Il2CppIsAssembliesLoaded();
void* Il2CppGetSingleton(const char *dllfilename, const char *namespaze, const char *className);
void* get_offset(const char *dllfilename, const char *namespaze, const char *className, const char *methodName, int argsCount);
size_t getFieldOffset(const char *dllfilename, const char *namespaceName, const char *className, const char *fieldName);

int GetObscuredIntValue(uint64_t location);
int GetObscuredBoolValue(uint64_t location);
void SetObscuredIntValue(uint64_t location, int value);
float GetObscuredFloatValue(uint64_t location);
void SetObscuredFloatValue(uint64_t location, float value);
template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    T vector [0];
    int getLength()
    {
        return max_length;
    }
    T *getPointer()
    {
        return vector;
    }

    template<typename V = T>
    std::vector<V> toCPPlist() {
        std::vector<V> ret;
        for (int i = 0; i < max_length; i++)
            ret.push_back(vector[i]);
        return std::move(ret);
    }
};

template <typename T>
struct monoList {
    void *unk0;
    void *unk1;
    monoArray<T> *items;
    int size;
    int version;

    T* getItems(){
        return items->getPointer();
    }

    int getSize(){
        return size;
    }

    int getVersion(){
        return version;
    }
};

template<typename TKey, typename TValue>
    struct Dictionary1 {
    struct Entry {
        int hashCode, next;
        TKey key;
        TValue value;
    };
    void *klass;
    void *monitor;
    monoArray<int> *buckets;
    monoArray<Entry> *entries;
    int count;
    int version;
    int freeList;
    int freeCount;
    void *comparer;
    monoArray<TKey> *keys;
    monoArray<TValue> *values;
    void *syncRoot;

    std::map<TKey, TValue> toMap() {
        std::map<TKey, TValue> ret;
        auto lst = entries->template toCPPlist();
        for (auto enter : lst)
            ret.insert(std::make_pair(enter.key, enter.value));
        return std::move(ret);
    }

    std::vector<TKey> getKeys() {
        std::vector<TKey> ret;
        auto lst = entries->template toCPPlist();
        for (auto enter : lst)
            ret.push_back(enter.key);
        return std::move(ret);
    }

    std::vector<TValue> getValues() {
        std::vector<TValue> ret;
        auto lst = entries->template toCPPlist();
        for (auto enter : lst)
            ret.push_back(enter.value);
        return std::move(ret);
    }

    int getSize() {
        return count;
    }

    int getVersion() {
        return version;
    }

    bool TryGet(TKey key, TValue &value);
    void Add(TKey key, TValue value);
    void Insert(TKey key, TValue value);
    bool Remove(TKey key);
    bool ContainsKey(TKey key);
    bool ContainsValue(TValue value);

    TValue Get(TKey key) {
        TValue ret;
        if (TryGet(key, ret))
            return ret;
        return {};
    }

    TValue operator [](TKey key) {
        return Get(key);
    }
};

union intfloat {
    int i;
    float f;
};

typedef struct _monoString
{
    void* klass;
    void* monitor;
    int length;    
    char chars[1];   
    int getLength()
    {
      return length;
    }
    char* getChars()
    {
        return chars;
    }
    NSString* toNSString()
    {
      return [[NSString alloc] initWithBytes:(const void *)(chars)
                     length:(NSUInteger)(length * 2)
                     encoding:(NSStringEncoding)NSUTF16LittleEndianStringEncoding];
    }

    char* toCString()
    {
      NSString* v1 = toNSString();
      return (char*)([v1 UTF8String]);  
    }
    std::string toCPPString()
    {
      return std::string(toCString());
    }
}monoString;
 