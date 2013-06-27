--
-- ------ Faith Emulator - Closed Source ------
-- Copyright (C) 2012 - 2013 Jean-Philippe Boivin
-- 
-- Please read the WARNING, DISCLAIMER and PATENTS
-- sections in the LICENSE file.
--

function processTask21(client, idx)

   if (idx == 0) then
      
      text(client, "I'm the well-known enchanter of the city. If you give me the required items, I can implant different spells in your equipments.")
      link(client, "Upgrade quality", 1)
      link(client, "Upgrade luck", 2)
      link(client, "I was just passing.", 255)
      pic(client, 0)
      create(client)
      
   elseif (idx == 1) then
      
      text(client, "You have " .. getMoney(client) .. " golds.")
      link(client, "exit", 255)
      pic(client, 0)
      create(client)
      
   elseif (idx == 2) then
   
   end

end
