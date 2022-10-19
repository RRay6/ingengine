#pragma once

struct Foo {
        int value{};
        
        // Let's make this Struct convert to and from ints for convenience, too.
        Foo( int v ) : value( v ) {}
        operator int() { return value; }
        // Just because we have an int constructor doesn't mean we don't still want an empty constructor.
        Foo() = default;
    };