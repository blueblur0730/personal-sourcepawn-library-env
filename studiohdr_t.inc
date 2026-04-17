#define VALID_MINIMUM_MEMORY_ADDRESS 0x10000

// char name[64].
methodmap CStudioHdr {
    public void pszName(char[] name, int maxlen) {
        PrintToServer("this: %d", this);
        Address studiohdr_t = LoadFromAddress(view_as<Address>(this) + view_as<Address>(0), NumberType_Int32);

        int index1 = LoadFromAddress(studiohdr_t + view_as<Address>(400), NumberType_Int8);
        PrintToServer("index1: %d, studiohdr_t: %d, 0x%x", index1, studiohdr_t, studiohdr_t);

        Address studiohdr2_t = LoadFromAddress(studiohdr_t + view_as<Address>(index1), NumberType_Int32);

        if (!index1 || studiohdr2_t == Address_Null || view_as<int>(studiohdr2_t) < VALID_MINIMUM_MEMORY_ADDRESS)
        {
            Stringt(studiohdr_t + view_as<Address>(12)).ToCharArray(name, maxlen);
        }
        else
        {
            int index2 = LoadFromAddress(studiohdr2_t + view_as<Address>(20), NumberType_Int8);
            PrintToServer("index2: %d", index2);

            Stringt(studiohdr2_t + view_as<Address>(index2)).ToCharArray(name, maxlen);
        }
    }
}