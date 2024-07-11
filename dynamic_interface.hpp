#include <bit> // IWYU pragma: keep
#include <type_traits>
#define _detail_EXPAND(...) _detail_EXPAND4(_detail_EXPAND4(_detail_EXPAND4(_detail_EXPAND4(__VA_ARGS__))))
#define _detail_EXPAND4(...) _detail_EXPAND3(_detail_EXPAND3(_detail_EXPAND3(_detail_EXPAND3(__VA_ARGS__))))
#define _detail_EXPAND3(...) _detail_EXPAND2(_detail_EXPAND2(_detail_EXPAND2(_detail_EXPAND2(__VA_ARGS__))))
#define _detail_EXPAND2(...) _detail_EXPAND1(_detail_EXPAND1(_detail_EXPAND1(_detail_EXPAND1(__VA_ARGS__))))
#define _detail_EXPAND1(...) __VA_ARGS__

#define _detail_EXPAND_(...) _detail_EXPAND_4(_detail_EXPAND_4(_detail_EXPAND_4(_detail_EXPAND_4(__VA_ARGS__))))
#define _detail_EXPAND_4(...) _detail_EXPAND_3(_detail_EXPAND_3(_detail_EXPAND_3(_detail_EXPAND_3(__VA_ARGS__))))
#define _detail_EXPAND_3(...) _detail_EXPAND_2(_detail_EXPAND_2(_detail_EXPAND_2(_detail_EXPAND_2(__VA_ARGS__))))
#define _detail_EXPAND_2(...) _detail_EXPAND_1(_detail_EXPAND_1(_detail_EXPAND_1(_detail_EXPAND_1(__VA_ARGS__))))
#define _detail_EXPAND_1(...) __VA_ARGS__

#define _detail_PARENS ()
#define _detail_foreach_macro_h(macro, a, ...) macro(a) \
__VA_OPT__(_detail_foreach_macro_a _detail_PARENS (macro, __VA_ARGS__))
#define _detail_foreach_macro_a() _detail_foreach_macro_h
#define _detail_foreach_macro(macro, ...) _detail_EXPAND(_detail_foreach_macro_h(macro, __VA_ARGS__))
#define _detail_map_macro_h(macro, a, ...) macro(a) \
__VA_OPT__(, _detail_map_macro_a _detail_PARENS (macro, __VA_ARGS__))
#define _detail_map_macro(macro, ...) _detail_EXPAND(_detail_map_macro_h(macro, __VA_ARGS__))
#define _detail_map_macro_a() _detail_map_macro_h
#define _detail_CONCAT_H(a, b) a ## b
#define _detail_CONCAT(a, b) _detail_CONCAT_H(a, b)
#define _detail_PARAM_LIST_H(b, c, f, ...) std::forward<decltype(c)>(c) __VA_OPT__(, _detail_PARAM_LIST_A _detail_PARENS (b, _detail_CONCAT(b, c), __VA_ARGS__))
#define _detail_PARAM_LIST_A() _detail_PARAM_LIST_H
#define _detail_PARAM_LIST(...) _detail_EXPAND_(_detail_PARAM_LIST_H(__VA_ARGS__))
#define _detail_PARAM_LIST_2H(b, c, f, ...) f c __VA_OPT__(, _detail_PARAM_LIST_2A _detail_PARENS (b, _detail_CONCAT(b, c), __VA_ARGS__))
#define _detail_PARAM_LIST_2A() _detail_PARAM_LIST_2H
#define _detail_PARAM_LIST2(...) _detail_EXPAND_(_detail_PARAM_LIST_2H(__VA_ARGS__))
#define _detail_EXPAND_LIST(...) __VA_ARGS__

#define _detail_INTERFACE_FUNCTION_PTR_DECL(type, name, ...) type (* name)(void* __VA_OPT__(, __VA_ARGS__));
#define _detail_LEAD_COMMA_H(...) __VA_OPT__(,)
#define _detail_INTERFACE_FPD_H(l) _detail_INTERFACE_FUNCTION_PTR_DECL l
#define _detail_INTERFACE_LIMP_H(l) _detail_INTERFACE_LAMBDA_IMPL l
#define _detail_INTERFACE_METHOD_H(l) _detail_INTERFACE_METHOD l
#define _detail_LEAD_COMMA_H_E(l) _detail_LEAD_COMMA_H l
#define _detail_INTERFACE_LAMBDA_IMPL(type, name, ...) \
name([](void * _vp __VA_OPT__(,_detail_PARAM_LIST2(a, _sig, __VA_ARGS__))) \
{return std::bit_cast<std::remove_cvref_t<_tp> *>(_vp)->name(__VA_OPT__(_detail_PARAM_LIST(a, _sig, __VA_ARGS__)));})
#define _detail_INTERFACE_METHOD(type, name, ...) \
type name(__VA_OPT__(_detail_PARAM_LIST2(a, _sig, __VA_ARGS__))) { \
    return _body.name(_body._ref __VA_OPT__(, _detail_PARAM_LIST(a, _sig, __VA_ARGS__))); \
}
#define _detail_DECLARE_INTERFACE(n, l) \
class n { \
    struct _impl { \
        void * _ref = nullptr; \
        _detail_foreach_macro(_detail_INTERFACE_FPD_H, _detail_EXPAND_LIST l)\
        _impl() = default; \
        template <typename _tp> \
        _impl(_tp&& v) \
        : _ref(const_cast<std::remove_cvref_t<_tp> *>(&v)) _detail_LEAD_COMMA_H_E(l) _detail_map_macro(_detail_INTERFACE_LIMP_H, _detail_EXPAND_LIST l) {}\
    } _body;\
    public: \
    n() = default; \
    template <typename _tp> \
    n(_tp&& v) : _body(v) {} \
    _detail_foreach_macro(_detail_INTERFACE_METHOD_H, _detail_EXPAND_LIST l)    \
    operator bool() {return _body._ref != nullptr;}\
};
#define DECLARE_INTERFACE(name, ...) _detail_DECLARE_INTERFACE(name, (__VA_ARGS__))
#define INTERFACE_METHOD(...) (__VA_ARGS__),

/*
THIS INTERFACE:
DECLARE_INTERFACE(example,
    (void, print, const char *)
)
EXPANDS TO:
    class example {
        struct _impl {
            void *_ref = nullptr;
            void (*print)(void *, const char *);
            _impl() = default;
            template <typename _tp>
            _impl(_tp &&v)
                : _ref(const_cast<std ::remove_cvref_t<_tp> *>(&v)),
                print([](void *_vp, const char *_sig) {
                    return std ::bit_cast<std ::remove_cvref_t<_tp> *>(_vp)
                        ->print(std ::forward<decltype(_sig)>(_sig));
                }) {}
        } _body;

    public:
        example() = default;
        template <typename _tp> example(_tp &&v) : _body(v) {}
        void print(const char *_sig) {
            return _body.print(_body._ref, std ::forward<decltype(_sig)>(_sig));
        }
        operator bool() { return _body._ref != nullptr; }
    };

*/
