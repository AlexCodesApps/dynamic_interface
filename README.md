# dynamic_interface
Unreadable Macro Hell To Create Something Cool

# How To Use
```cpp
DECLARE_INTERFACE(name,
    (type, method, arg_types...), // You Can Declare A Method Like This
    INTERFACE_METHOD(type, method, arg_types...) // Or This
)
```
```cpp
// THIS INTERFACE:
DECLARE_INTERFACE(example,
    (void, print, const char *)
)
// EXPANDS TO:
/*
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
```
